#include "Vertex.h"

Vertex::Vertex(const Vector3& p, const Color& c, float _u, float _v)
	: pos(p), color(c), u(_u), v(_v)
{

}

Vertex::~Vertex()
{

}

void Vertex::LerpVertexData(Vertex& left, const Vertex& right, float t)
{
	color = Color::Lerp(left.color, right.color, t);
	u = LerpFloat(left.u, right.u, t);
	v = LerpFloat(left.v, right.v, t);
}

void Vertex::Print()
{
	std::cout << "Vector3: " << pos.x << " " << pos.y << " " << pos.z;
	std::cout << " Color: "  << color.r << " " << color.g << " " << color.b <<std::endl;
}
