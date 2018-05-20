/*******************************************************************
 * \file Vertex.h
 *
 * \author puppet_master
 * \date 2018/05/20
 * \https://blog.csdn.net/puppet_master
 * \顶点类，包含了顶点的位置，颜色，纹理坐标，包括插值功能
 *******************************************************************/
#include "Vector3.h"
#include "Color.h"

#pragma once
class Vertex
{
public:
	Vector3 pos;
	Color color;
	float u, v;

	Vertex(const Vector3& p, const Color& c, float u, float v);
	~Vertex();

	void LerpVertexData(Vertex& left, const Vertex& right, float t);
	void Print();

	static float LerpFloat(float v1, float v2, float t){ return v1 + (v2 - v1) * t;}
};

