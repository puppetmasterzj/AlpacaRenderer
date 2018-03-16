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

	static float LerpFloat(float v1, float v2, float t){ return v1 * t + v2 * (1 - t);}
};

