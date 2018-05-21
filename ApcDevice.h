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

	void DrawPrimitive(Vertex v1, Vertex v2, Vertex v3, const Matrix& mvp);
	void RasterizeTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawTopFlatTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawBottomFlatTrangle(Vertex v1, Vertex v2, Vertex v3);
	void DrawLine(Vertex v1, Vertex v2);
	void DrawPixel(int x, int y, const Color& color);

	Matrix GenMVPMatrix();
	Matrix GenTranslateMatrix(const Vector3& v);
	Matrix GenScaleMatrix(const Vector3& v);
	Matrix GenRotationMatrix(const Vector3& rotAngle);
	Matrix GenRotationXMatrix(float angle);
	Matrix GenRotationYMatrix(float angle);
	Matrix GenRotationZMatrix(float angle);
	Matrix GenCameraMatrix(const Vector3& eyePos, const Vector3& lookPos, const Vector3& upAxis);
	Matrix GenProjectionMatrix(float fov, float aspect, float nearPanel, float farPanel);

	bool ZTestAndWrite(int x, int y, float depth);
	//简单CVV剔除，只考虑三顶点均不在的情况，未做边界三角形重新构建
	bool SimpleCVVCullCheck(const Vertex& vertex);
	//准备光栅化，透视投影除法，视口映射，三角形数据准备
	void PrepareRasterization(Vertex& vertex);

	//以下为测试光栅化函数，单独的画线，画三角形，不带其他顶点数据的绘制
	void DrawTrangle3D(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Matrix& mvp);
	void DrawTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawTopFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawBottomFlatTrangle(int x0, int y0, int x1, int y1, int x2, int y2);
	void DrawLine(int x0, int y0, int x1, int y1);
	void DrawPixel(int x, int y);
	Vector3 GetScreenCoord(const Vector3& v);
	
};

