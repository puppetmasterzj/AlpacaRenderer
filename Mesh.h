#pragma once
#include "Vertex.h"
#include "ApcDevice.h"
#include <vector>

class Mesh
{
private:
	std::vector<Vertex> vertexBuffer;
	std::vector<int> indexBuffer;
public:
	Mesh();
	~Mesh();

	static Mesh* CreateTrangle();
	static Mesh* CreatePlane();
	static Mesh* CreateCube();

	void DrawElement(ApcDevice* device);
};

