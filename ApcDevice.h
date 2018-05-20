/*******************************************************************
 * \file ApcDevice.h
 *
 * \author puppet_master
 * \date 2018/05/20添加注释
 * \https://blog.csdn.net/puppet_master
 * \羊驼软渲染器AlpacaSoftRenderer的主要实现
 * \包含MVP矩阵生成，视口映射，简单裁剪，深度测试，光栅化，数据插值
 * \包含部分测试函数，基本的2D绘制
 *******************************************************************/
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
	float** zBuffer;

public:
	ApcDevice();
	~ApcDevice();

	void InitDevice(HDC hdc, int screenWidth, int screenHeight);
	void ReleaseDevice();
	void Clear();

	bool ZTest(int x, int y, float depth);
	void DrawPixel(int x, int y);
	void DrawPixel(int x, int y, const Color& color);
	void DrawLine(int x0, int y0, int x1, int y1);
	void DrawTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawTrangle2D(Vertex v1, Vertex v2, Vertex v3);
	void DrawPrimitive(Vertex v1, Vertex v2, Vertex v3, const Matrix& mvp);

	void DrawTrangle3D(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Matrix& mvp);
	
	Matrix GenMVPMatrix();
	Matrix GenTranslateMatrix(const Vector3& v);
	Matrix GenScaleMatrix(const Vector3& v);
	Matrix GenRotationMatrix(const Vector3& rotAngle);
	Matrix GenRotationXMatrix(float angle);
	Matrix GenRotationYMatrix(float angle);
	Matrix GenRotationZMatrix(float angle);

	Matrix GenCameraMatrix(const Vector3& eyePos, const Vector3& lookPos, const Vector3& upAxis);
	Matrix GenProjectionMatrix(float fov, float aspect, float nearPanel, float farPanel);

	Vector3 GetScreenCoord(const Vector3& v);

private:
	void DrawTopFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawBottomFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);

	void DrawTopFlatTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawBottomFlatTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawLine(Vertex v1, Vertex v2);
};

