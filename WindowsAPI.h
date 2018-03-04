#pragma once

#include "Stdfx.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class WindowsAPI
{
private:
	
	
	static HDC hdc;
	static HDC screenHDC;
public:
	WindowsAPI();
	~WindowsAPI();

	void CreateSystemWindow();
	void Update();
	static LRESULT OnEvent(HWND, UINT, WPARAM, LPARAM);

	static void DrawPixel(int x, int y);
	static const int windowWidth = 800;
	static const int windowHeight = 600;
	const char* windowTitle = "—ÚÕ’‰÷»æ∆˜";
};
