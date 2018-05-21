#include "ApcDevice.h"
#include "Matrix.h"

ApcDevice::ApcDevice()
{
}


ApcDevice::~ApcDevice()
{
}

void ApcDevice::InitDevice(HDC hdc, int screenWidth, int screenHeight)
{
	screenHDC = hdc;
	deviceWidth = screenWidth;
	deviceHeight = screenHeight;
	
	zBuffer = new float*[deviceHeight];
	for (int i = 0; i < deviceHeight; i++)
	{
		zBuffer[i] = new float[deviceWidth];
	}

	tex = new Texture();
	tex->LoadTexture("icon.bmp");
}

void ApcDevice::ReleaseDevice()
{
	for (int i = 0; i < deviceHeight; i++)
	{
		delete[] zBuffer[i];
	}
}

void ApcDevice::DrawPrimitive(Vertex v1, Vertex v2, Vertex v3, const Matrix& mvp)
{
	//对顶点位置进行MVP矩阵变换
	v1.pos = mvp.MultiplyVector3(v1.pos);
	v2.pos = mvp.MultiplyVector3(v2.pos);
	v3.pos = mvp.MultiplyVector3(v3.pos);

	//透视除法，视口映射，数据准备（全部改为1/z）
	PrepareRasterization(v1);
	PrepareRasterization(v2);
	PrepareRasterization(v3);

	RasterizeTrangle(v1, v2, v3);
}

void ApcDevice::RasterizeTrangle(Vertex v0, Vertex v1, Vertex v2)
{
	//按照y进行排序，使y0 < y1 < y2
	if (v1.pos.y < v0.pos.y)
		std::swap(v0, v1);
	if (v2.pos.y < v0.pos.y)
		std::swap(v0, v2);
	if (v2.pos.y < v1.pos.y)
		std::swap(v1, v2);

	int ty0 = v0.pos.y;
	int ty1 = v1.pos.y;
	int ty2 = v2.pos.y;
	if (ty0 == ty1)	//平顶三角形
	{
		DrawTopFlatTrangle(v0, v1, v2);
	}
	else if (ty1 == ty2) //平底三角形
	{
		DrawBottomFlatTrangle(v0, v1, v2);
	}
	else			//拆分为一个平顶三角形和一个平底三角形
	{
		//中心点为直线(x0, y0)，(x2, y2)上取y1的点
		float x3 = (v1.pos.y - v0.pos.y) * (v2.pos.x - v0.pos.x) / (v2.pos.y - v0.pos.y) + v0.pos.x;
		float y3 = v1.pos.y;
		float t = (y3 - v0.pos.y) / (v2.pos.y - v0.pos.y);

		Vertex v3(Vector3(x3, y3, 0), Color(0, 0, 0, 0), 0, 0);
	
		v3.LerpVertexData(v0, v2, t);
	
		DrawBottomFlatTrangle(v0, v1, v3);
		DrawTopFlatTrangle(v1, v3, v2);
	}
}

void ApcDevice::DrawTopFlatTrangle(Vertex v0, Vertex v1, Vertex v2)
{
	float x0 = v0.pos.x;
	float y0 = v0.pos.y;
	float x1 = v1.pos.x;
	float y1 = v1.pos.y;
	float x2 = v2.pos.x;
	float y2 = v2.pos.y;
	for (float y = y0; y <= y2; y++)
	{
		float t = (y - y0) / (y2 - y0);

		float xl = (y - y0) * (x2 - x0) / (y2 - y0) + x0;
		Vertex vl(Vector3(xl, y, 0), Color(0, 0, 0, 0), 0, 0);
		vl.LerpVertexData(v0, v2, t);

		float xr = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
		Vertex vr(Vector3(xr, y, 0), Color(0, 0, 0, 0), 0, 0);
		vr.LerpVertexData(v1, v2, t);

		DrawLine(vl, vr);
	}
}

void ApcDevice::DrawBottomFlatTrangle(Vertex v0, Vertex v1, Vertex v2)
{
	float x0 = v0.pos.x;
	float y0 = v0.pos.y;
	float x1 = v1.pos.x;
	float y1 = v1.pos.y;
	float x2 = v2.pos.x;
	float y2 = v2.pos.y;
	for (float y = y0; y <= y1; y++)
	{
		float t = (y - y0) / (y2 - y0);

		float xl = (y - y1) * (x0 - x1) / (y0 - y1) + x1;
		Vertex vl(Vector3(xl, y, 0), Color(0, 0, 0, 0), 0, 0);
		vl.LerpVertexData(v0, v1, t);

		float xr = (y - y2) * (x0 - x2) / (y0 - y2) + x2;
		Vertex vr(Vector3(xr, y, 0), Color(0, 0, 0, 0), 0, 0);
		vr.LerpVertexData(v0, v2, t);

		DrawLine(vl, vr);
	}
}

void ApcDevice::DrawLine(Vertex v0, Vertex v1)
{
	float x0 = v0.pos.x;
	float x1 = v1.pos.x;
	float y0 = v0.pos.y;
	float y1 = v1.pos.y;
	//只考虑x方向扫描线即可
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

	int x = x0;
	int y = y0;

	int errorValue = dy2 - dx;
	for (int i = 0; i <= dx; i++)
	{
		float t = (x - x0) / (x1 - x0);
		float z = Vertex::LerpFloat(v0.pos.z, v1.pos.z, t);
		if (ZTest(x, y, z))
		{
			float u = Vertex::LerpFloat(v0.u, v1.u, t);
			float v = Vertex::LerpFloat(v0.v, v1.v, t);
			//Color c = Color::Lerp(v0.color, v1.color, t);
			float realz = 1.0f / z;
			Color c = tex->Sample(u * realz, v * realz);
			DrawPixel(x, y, c);
		}

		x += stepx;
		errorValue += dy2;
		if (errorValue >= 0)
		{
			errorValue -= dx2;
			y += stepy;
		}
	}
}

bool ApcDevice::ZTest(int x, int y, float depth)
{
	if (x >= 0 && x < deviceWidth && y >= 0 && y < deviceHeight)
	{
		if (zBuffer[y][x] <= depth)
		{
			zBuffer[y][x] = depth;
			return true;
		}
	}
	return false;
}

void ApcDevice::DrawPixel(int x, int y, const Color& color)
{
	SetPixel(screenHDC, x, y, RGB(255 * color.r, 255 * color.g, 255 * color.b));
}

void ApcDevice::DrawPixel(int x, int y)
{
	SetPixel(screenHDC, x, y, RGB(255, 255, 0));
}

void ApcDevice::Clear()
{
	BitBlt(screenHDC, 0, 0, deviceWidth, deviceHeight, NULL, NULL, NULL, BLACKNESS);
	//ClearZ
	for (int i = 0; i < deviceHeight; i++)
	{
		for (int j = 0; j < deviceWidth; j++)
		{
			zBuffer[i][j] = 0.0f;
		}
	}
}

int count = 0;
Matrix ApcDevice::GenMVPMatrix()
{
	Matrix scaleM = GenScaleMatrix(Vector3(1.0f, 1.0f, 1.0f));
	//Matrix rotM = GenRotationMatrix(Vector3(0, 45.0f, 0));
	Matrix rotM = GenRotationMatrix(Vector3(count++ * 0.04f, count++ * 0.04f, 0));
	Matrix transM = GenTranslateMatrix(Vector3(0, 0, 0));
	Matrix worldM = scaleM * rotM * transM;
	Matrix cameraM = GenCameraMatrix(Vector3(0, 0, -5), Vector3(0, 0, 0), Vector3(0, 1, 0));
	Matrix projM = GenProjectionMatrix(60.0f, (float)deviceWidth / deviceHeight, 0.1f, 30.0f);

	return worldM * cameraM * projM;
}


Matrix ApcDevice::GenTranslateMatrix(const Vector3& v)
{
	Matrix m;
	m.Identity();
	m.value[3][0] = v.x;
	m.value[3][1] = v.y;
	m.value[3][2] = v.z;
	return m;
}

Matrix ApcDevice::GenScaleMatrix(const Vector3& v)
{
	Matrix m;
	m.Identity();
	m.value[0][0] = v.x;
	m.value[1][1] = v.y;
	m.value[2][2] = v.z;
	return m;
}

//旋转矩阵推导:http://www.cnblogs.com/luweimy/p/4121789.html#3743809
Matrix ApcDevice::GenRotationMatrix(const Vector3& rotAngle)
{
	Matrix rotX = GenRotationXMatrix(rotAngle.x);
	Matrix rotY = GenRotationYMatrix(rotAngle.y);
	Matrix rotZ = GenRotationZMatrix(rotAngle.z);
	return rotX * rotY * rotZ;
}

Matrix ApcDevice::GenRotationXMatrix(float angle)
{
	Matrix m;
	m.Identity();
	float cosValue = cos(angle);
	float sinValue = sin(angle);
	m.value[1][1] = cosValue;
	m.value[1][2] = sinValue;
	m.value[2][1] = -sinValue;
	m.value[2][2] = cosValue;
	return m;
}

Matrix ApcDevice::GenRotationYMatrix(float angle)
{
	Matrix m;
	m.Identity();
	float cosValue = cos(angle);
	float sinValue = sin(angle);
	m.value[0][0] = cosValue;
	m.value[0][2] = -sinValue;
	m.value[2][0] = sinValue;
	m.value[2][2] = cosValue;
	return m;
}

Matrix ApcDevice::GenRotationZMatrix(float angle)
{
	Matrix m;
	m.Identity();
	float cosValue = cos(angle);
	float sinValue = sin(angle);
	m.value[0][0] = cosValue;
	m.value[0][1] = sinValue;
	m.value[1][0] = -sinValue;
	m.value[1][1] = cosValue;
	return m;
}

//相机矩阵推导:http://blog.csdn.net/popy007/article/details/5120158
//DX版本实现：http://www.cnblogs.com/mikewolf2002/archive/2012/03/11/2390669.html
Matrix ApcDevice::GenCameraMatrix(const Vector3& eyePos, const Vector3& lookPos, const Vector3& upAxis)
{
	Vector3 lookDir = lookPos - eyePos;
	lookDir.Normalize();

	Vector3 rightDir = Vector3::Cross(upAxis, lookDir);
	rightDir.Normalize();

	Vector3 upDir = Vector3::Cross(lookDir, rightDir);
	upDir.Normalize();

	//构建一个坐标系，将vector转化到该坐标系，相当于对坐标系进行逆变换
	//C = RT,C^-1 = (RT)^-1 = (T^-1) * (R^-1),Translate矩阵逆矩阵直接对x,y,z取反即可；R矩阵为正交矩阵，故T^-1 = Transpose(T)
	//最终Camera矩阵为(T^-1) * Transpose(T)，此处可以直接给出矩阵乘法后的结果，减少运行时计算
	float transX = -Vector3::Dot(rightDir, eyePos);
	float transY = -Vector3::Dot(upDir, eyePos);
	float transZ = -Vector3::Dot(lookDir, eyePos);
	Matrix m;
	m.value[0][0] = rightDir.x;  m.value[0][1] = upDir.x;  m.value[0][2] = lookDir.x;  m.value[0][3] = 0;
	m.value[1][0] = rightDir.y;	 m.value[1][1] = upDir.y;  m.value[1][2] = lookDir.y;  m.value[1][3] = 0;
	m.value[2][0] = rightDir.z;  m.value[2][1] = upDir.z;  m.value[2][2] = lookDir.z;  m.value[2][3] = 0;
	m.value[3][0] = transX;		 m.value[3][1] = transY;   m.value[3][2] = transZ;	   m.value[3][3] = 1;
	return m;
}

//透视投影矩阵推导:http://blog.csdn.net/popy007/article/details/1797121#comments
Matrix ApcDevice::GenProjectionMatrix(float fov, float aspect, float nearPanel, float farPanel)
{
	float tanValue = tan(0.5f * fov * 3.1415 / 180);

	Matrix proj;
	proj.value[0][0] = 1.0f / (tanValue * aspect);
	proj.value[1][1] = 1.0f / (tanValue);
	proj.value[2][2] = farPanel / (farPanel - nearPanel);
	proj.value[3][2] = -nearPanel * farPanel / (farPanel - nearPanel);
	proj.value[2][3] = 1;
	return proj;
}

void ApcDevice::PrepareRasterization(Vertex& vertex)
{
	//透视除法&视口映射
	//齐次坐标转化，除以w，然后从-1,1区间转化到0，1区间，+ 1然后/2 再乘以屏幕长宽
	float reciprocalW = 1.0f / vertex.pos.w;
	vertex.pos.x = (vertex.pos.x * reciprocalW + 1.0f) * 0.5f * deviceWidth;
	vertex.pos.y = (1.0f - vertex.pos.y * reciprocalW) * 0.5f * deviceHeight;
	//将其他数据转化为1/z
	vertex.pos.z = 1.0f / vertex.pos.z;
	vertex.u *= reciprocalW;
	vertex.v *= reciprocalW;
}

//////////////////////////////////////////////////////////////////////////
//以下为测试光栅化函数，单独的画线，画三角形，不带其他顶点数据的绘制

//https://zhuanlan.zhihu.com/p/20213658
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
	/*float errorValue = 0;
	for (int x = x0, y = y0; x <= x1; x++)
	{
	DrawPixel(x, y);
	errorValue += (float)dy / dx;
	if (errorValue > 0.5)
	{
	errorValue = errorValue - 1;
	y++;
	}
	}*/

	int x = x0;
	int y = y0;
	int errorValue;

	//改为整数计算，去掉除法
	if (dy < dx)
	{
		errorValue = dy2 - dx;
		for (int i = 0; i <= dx; i++)
		{
			DrawPixel(x, y);
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
			DrawPixel(x, y);
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

void ApcDevice::DrawTrangle3D(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Matrix& mvp)
{
	Vector3 vt1 = mvp.MultiplyVector3(v1);
	Vector3 vt2 = mvp.MultiplyVector3(v2);
	Vector3 vt3 = mvp.MultiplyVector3(v3);

	Vector3 vs1 = GetScreenCoord(vt1);
	Vector3 vs2 = GetScreenCoord(vt2);
	Vector3 vs3 = GetScreenCoord(vt3);

	DrawTrangle(vs1.x, vs1.y, vs2.x, vs2.y, vs3.x, vs3.y);
}

Vector3 ApcDevice::GetScreenCoord(const Vector3& v)
{
	float reciprocalW = 1.0f / v.w;
	float x = (v.x * reciprocalW + 1.0f) * 0.5f * deviceWidth;
	float y = (1.0f - v.y * reciprocalW) * 0.5f * deviceHeight;
	float z = 1 / v.z;
	return Vector3(x, y, z);
}
