#include "WindowsAPI.h"
#include "ApcDevice.h"

WindowsAPI::WindowsAPI()
{
}


WindowsAPI::~WindowsAPI()
{
}

HDC WindowsAPI::hdc = NULL;
HDC WindowsAPI::screenHDC = NULL;

void WindowsAPI::CreateSystemWindow()
{
	WNDCLASS wndClass = { CS_BYTEALIGNCLIENT, (WNDPROC)OnEvent, 0, 0, 0, NULL, NULL, NULL, NULL, TEXT(windowTitle) };
	wndClass.hInstance = GetModuleHandle(NULL);

	if (!RegisterClass(&wndClass))
		return;

	HWND handler = CreateWindow(TEXT(windowTitle), TEXT(windowTitle), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		0, 0, 0, 0, NULL, NULL, wndClass.hInstance, NULL);
	if (handler == NULL)
		return;

	hdc = GetDC((handler));
	screenHDC = CreateCompatibleDC(hdc);
	ReleaseDC(handler, hdc);

	BITMAPINFO bitmapInfo = { { sizeof(BITMAPINFOHEADER),windowWidth, windowHeight, 1, 32, BI_RGB, windowWidth * windowHeight * 4, 0, 0, 0, 0 } };
	LPVOID ptr;
	//创建设备无关的位图
	HBITMAP bitmapHandler = CreateDIBSection(screenHDC, &bitmapInfo, DIB_RGB_COLORS, &ptr, 0, 0);
	if (bitmapHandler == NULL)
		return;

	HBITMAP screenObject = (HBITMAP)SelectObject(screenHDC, bitmapHandler);
	//unsigned char* screen_fb = NULL;
	//screen_fb = (unsigned char*)ptr;

	SetWindowPos(handler, NULL, 300, 200, windowWidth, windowHeight, (SWP_NOCOPYBITS | SWP_NOZORDER | SWP_SHOWWINDOW));

	ShowWindow(handler, SW_NORMAL);

	//char* frameBuffer = (char*)ptr;

}

void WindowsAPI::Update()
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT WindowsAPI::OnEvent(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	switch (msg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hwnd, &ps);

		//ApcDevice::DrawLine(0, 0, 1000, 1000);
		//ApcDevice::DrawLine(0, 0, 500, 1000);
		//ApcDevice::DrawLine(0, 0, 1000, 500);
		//ApcDevice::DrawLine(500, 1000, 0, 0);
		//ApcDevice::DrawLine(1000, 500, 0, 0);

		//ApcDevice::DrawTrangle(0, 0, 0, 300, 400, 300);
		//ApcDevice::DrawTrangle(0, 0, 200, 0, 300, 500);
		////ApcDevice::DrawTrangle(300, 0, 400, 400, 500, 500);
		//ApcDevice::DrawTrangle(300, 0, 800, 600, 500, 500);
		/*Vector3 v1(1, 2, 3);
		Vector3 v2(4, 5, 6);
		(v1 + v2).Print();
		(v1 - v2).Print();
		(v1 * 3).Print();
		(v1 / 3).Print();
		std::cout << v1.Magnitude() << std::endl;
		std::cout << Vector3::Dot(v1, v2) << std::endl;
		Vector3::Cross(v1, v2).Print();

		Matrix m;
		m.Identity();
		m.Print();
		m.value[0][3] = 8;
		m.Print();
		m.Transpose();
		m.Print();

		Vector3 v3(1, 1, 0);
		Matrix mt = Matrix::GenTranslateMatrix(Vector3(1, 0, 0));
		Matrix ms = Matrix::GenScaleMatrix(Vector3(.5f, .5f, .5f));
		Matrix resultM = mt * ms;
		v3 = resultM.MultiplyVector3(v3);
		v3.Print();*/

		Vector3 v1(0, 5, 1); Color c1(1.0f, 0, 0, 1.0f);
		Vector3 v2(4, 3, 1); Color c2(0, 1.0f, 0, 1.0f);
		Vector3 v3(4, 0, 1); Color c3(0, 0, 1.0f, 1.0f);
		//ApcDevice::DrawTrangle3D(v1, v2, v3);
		Vertex p1(v1, c1);
		Vertex p2(v2, c2);
		Vertex p3(v3, c3);
		ApcDevice::DrawPrimitive(p1, p2, p3);


		BitBlt(hdc, 0, 0, windowWidth, windowHeight, screenHDC, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void WindowsAPI::DrawPixel(int x, int y, const Color& color)
{
	SetPixel(screenHDC, x, y, RGB(255 * color.r, 255 * color.g, 255 * color.b));
}

void WindowsAPI::DrawPixel(int x, int y)
{
	SetPixel(screenHDC, x, y, RGB(255, 255, 0));
}
