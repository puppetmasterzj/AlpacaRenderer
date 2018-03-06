#include "Vector3.h"
#include "Color.h"

#pragma once
class Vertex
{
public:
	Vector3 pos;
	Color color;

	Vertex(const Vector3& p, const Color& c);
	~Vertex();

	void LerpVertexData(Vertex& left, const Vertex& right, float t);
};

