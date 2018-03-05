//羊驼渲染器主要实现 Device
#pragma once
#include "Stdfx.h"
#include "Vector3.h"
#include "Matrix.h"

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

	static void DrawTrangle3D(const Vector3& v1, const Vector3& v2, const Vector3& v3);
	static Matrix GenTranslateMatrix(const Vector3& v);
	static Matrix GenRotationMatrix(const Vector3& rotAxis, float angle);
	static Matrix GenScaleMatrix(const Vector3& v);
	static Matrix GenCameraMatrix(const Vector3& eyePos, const Vector3& lookPos, const Vector3& upAxis);
	static Matrix GenProjectionMatrix(float fov, float aspect, float nearPanel, float farPanel);
	static Vector3 GetScreenCoord(const Vector3& v);
private:
	static void DrawTopFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	static void DrawBottomFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	
};

