#include "ApcDevice.h"
#include "WindowsAPI.h"
#include "Matrix.h"

ApcDevice::ApcDevice()
{
}


ApcDevice::~ApcDevice()
{
}

void ApcDevice::DrawLine(int x0, int y0, int x1, int y1)
{
	int dx = x1 - x0;
	int dy = y1 - y0;

	int stepx = 1;
	int stepy = 1;
	
	if (dx < 0)
	{
		stepx = -1;
		dx = -dx;
	}

	if (dy < 0)
	{
		stepy = -1;
		dy = -dy;
	}

	int dy2 = dy << 1;
	int dx2 = dx << 1;

	//斜率k = dy / dx
	//以斜率小于1为例，x轴方向每单位都应该绘制一个像素，x累加即可，而y需要判断。
	//误差项errorValue = errorValue + k，一旦k > 1，errorValue = errorValue - 1，保证0 < errorValue < 1
	//errorValue > 0.5时，距离y + 1点较近，因而y++，否则y不变。

	//float errorValue = 0;
	//for (int x = x0, y = y0; x <= x1; x++)
	//{
	//	WindowsAPI::DrawPixel(x, y);
	//	errorValue += (float)dy / dx;
	//	if (errorValue > 0.5)
	//	{
	//		errorValue = errorValue - 1;
	//		y++;
	//	}
	//}

	int x = x0;
	int y = y0;
	int errorValue;

	//改为整数计算，去掉除法
	if (dy < dx)
	{
		errorValue = dy2 - dx;
		for (int i = 0; i <= dx; i++)
		{
			WindowsAPI::DrawPixel(x, y);
			x += stepx;
			errorValue += dy2;
			if (errorValue >= 0)
			{
				errorValue -= dx2;
				y += stepy;
			}
		}
	}
	else
	{
		errorValue = dx2 - dy;
		for (int i = 0; i <= dy; i++)
		{
			WindowsAPI::DrawPixel(x, y);
			y += stepy;
			errorValue += dx2;
			if (errorValue >= 0)
			{
				errorValue -= dy2;
				x += stepx;
			}
		}
	}
}

//https://zhuanlan.zhihu.com/p/20148016?refer=alchemelon
void ApcDevice::DrawTrangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	//按照y进行排序，使y0 < y1 < y2
	if (y1 < y0)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (y2 < y0)
	{
		std::swap(x0, x2);
		std::swap(y0, y2);
	}
	if (y2 < y1)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	if (y0 == y1)	//平顶三角形
	{
		DrawTopFlatTrangle(x0, y0, x1, y1, x2, y2);
	}
	else if (y1 == y2) //平底三角形
	{
		DrawBottomFlatTrangle(x0, y0, x1, y1, x2, y2);
	}
	else			//拆分为一个平顶三角形和一个平底三角形
	{
		//中心点为直线(x0, y0)，(x2, y2)上取y1的点
		int x3 = (y1 - y0) * (x2 - x0) / (y2 - y0) + x0;
		int y3 = y1;

		//进行x排序，此处约定x2较小
		if (x1 > x3)
		{
			std::swap(x1, x3);
			std::swap(y1, y3);
		}
		DrawBottomFlatTrangle(x0, y0, x1, y1, x3, y3);
		DrawTopFlatTrangle(x1, y1, x3, y3, x2, y2);
	}
}

void ApcDevice::DrawBottomFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	for (int y = y0; y <= y1; y++)
	{
		int xl = (y - y1) * (x0 - x1) / (y0 - y1) + x1;
		int xr = (y - y2) * (x0 - x2) / (y0 - y2) + x2;
		DrawLine(xl, y, xr, y);
	}
}

void ApcDevice::DrawTopFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	for (int y = y0; y <= y2; y++)
	{
		int xl = (y - y0) * (x2 - x0) / (y2 - y0) + x0;
		int xr = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
		DrawLine(xl, y, xr, y);
	}
}

void ApcDevice::DrawTrangle3D(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{
	Matrix scaleM = Matrix::GenScaleMatrix(Vector3(1.0f, 1.0f, 1.0f));
	Matrix transM = Matrix::GenTranslateMatrix(Vector3(0.5f, 0.5f, 0.0f));
	Matrix worldM = scaleM * transM;
	Matrix cameraM = Matrix::GenCameraMatrix(Vector3(0, 0, -1.0f), Vector3(0, 0, 0), Vector3(0, 1.0f, 0));
	Matrix projM = Matrix::GenProjectionMatrix(60.0f, 1.0f, 0.5f, 30.0f);

	Matrix transformM = worldM * cameraM * projM;

	Vector3 vt1 = transformM.MultiplyVector3(v1);
	Vector3 vt2 = transformM.MultiplyVector3(v2);
	Vector3 vt3 = transformM.MultiplyVector3(v3);

	Vector3 vs1 = GetScreenCoord(vt1);
	Vector3 vs2 = GetScreenCoord(vt2);
	Vector3 vs3 = GetScreenCoord(vt3);

	DrawTrangle(vs1.x, vs1.y, vs2.x, vs2.y, vs3.x, vs3.y);
}

//齐次坐标转化，除以w，然后从-1,1区间转化到0，1区间，+ 1然后/2
Vector3 ApcDevice::GetScreenCoord(const Vector3& v)
{
	float x = (v.x / v.w + 1) * 0.5f * WindowsAPI::windowWidth;
	float y = (1.0f - v.y / v.w) * 0.5f * WindowsAPI::windowHeight;
	float z = v.z / v.w;
	return Vector3(x, y, z);
}
