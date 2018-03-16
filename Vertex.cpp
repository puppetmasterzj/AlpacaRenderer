#include "Vertex.h"

Vertex::Vertex(const Vector3& p, const Color& c)
	: pos(p), color(c)
{

}

Vertex::~Vertex()
{

}

void Vertex::LerpVertexData(Vertex& left, const Vertex& right, float t)
{
	color = Color::Lerp(left.color, right.color, t);
}

void Vertex::Print()
{
	std::cout << "Vector3: " << pos.x << " " << pos.y << " " << pos.z;
	std::cout << " Color: "  << color.r << " " << color.g << " " << color.b <<std::endl;
}
