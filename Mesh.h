#pragma once
#include "Vertex.h"
#include <vector>

class Mesh
{
private:
	std::vector<Vertex> vertexList;
public:
	Mesh();
	~Mesh();
};

