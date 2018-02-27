#include "ApcDevice.h"



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

void ApcDevice::DrawTrangle(int x0, int y0, int x1, int y1, int x2, int y2)
{
	//平底三角形
	for (int y = y0; y < y1; y++)
	{
		int xl = (y - y1) * (x0 - x1) / (y0 - y1) + x1;
		int xr = (y - y2) * (x0 - x2) / (y0 - y2) + x2;
		DrawLine(xl, y, xr, y);
	}
}
