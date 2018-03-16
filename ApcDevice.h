//羊驼渲染器主要实现 Device
#pragma once
#include "Stdfx.h"
#include "Matrix.h"
#include "Vertex.h"
#include "Texture.h"
class ApcDevice
{
private:
	int deviceWidth;
	int deviceHeight;
	HDC screenHDC;
	Texture* tex;

public:
	ApcDevice();
	~ApcDevice();

	void InitDevice(HDC hdc, int screenWidth, int screenHeight);
	void Clear();

	void DrawPixel(int x, int y);
	void DrawPixel(int x, int y, const Color& color);
	void DrawLine(int x0, int y0, int x1, int y1);
	void DrawTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawTrangle2D(Vertex v1, Vertex v2, Vertex v3);
	void DrawPrimitive(Vertex v1, Vertex v2, Vertex v3);

	void DrawTrangle3D(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	Matrix GenTranslateMatrix(const Vector3& v);
	Matrix GenRotationMatrix(const Vector3& rotAngle);
	Matrix GenScaleMatrix(const Vector3& v);
	Matrix GenCameraMatrix(const Vector3& eyePos, const Vector3& lookPos, const Vector3& upAxis);
	Matrix GenProjectionMatrix(float fov, float aspect, float nearPanel, float farPanel);
	Vector3 GetScreenCoord(const Vector3& v);

	Matrix GenRotationXMatrix(float angle);
	Matrix GenRotationYMatrix(float angle);
	Matrix GenRotationZMatrix(float angle);
private:
	void DrawTopFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawBottomFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);

	void DrawTopFlatTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawBottomFlatTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawLine(Vertex v1, Vertex v2);
	
};

