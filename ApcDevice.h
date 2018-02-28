//羊驼渲染器主要实现 Device
#pragma once
#include "Stdfx.h"

class ApcDevice
{
private:
	int deviceWidth;
	int deviceHeight;

public:
	ApcDevice();
	~ApcDevice();

	static void DrawLine(int x0, int y0, int x1, int y1);
	static void DrawTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
private:
	static void DrawTopFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	static void DrawBottomFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	
};

