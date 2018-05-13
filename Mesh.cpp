#include "Mesh.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

Mesh* Mesh::CreateTrangle()
{
	Mesh* mesh = new Mesh();
	mesh->AddVertexData(-1, -1, 0, 0, 0);
	mesh->AddVertexData( 1, -1, 0, 0, 1);
	mesh->AddVertexData( 0,  0, 0, 1, 1);
	int indexArray[] = { 0, 1, 2 };
	//数组直接转vector https://blog.csdn.net/sagittarius_warrior/article/details/54089242
	std::vector<int> index(indexArray, indexArray + sizeof(indexArray) / sizeof(int));
	mesh->indexBuffer = index;
	return mesh;
}

Mesh* Mesh::CreatePlane()
{
	Mesh* mesh = new Mesh();
	mesh->AddVertexData(-1,  1, 0, 0, 0, Color(1.0f, 0, 0, 1.0f));
	mesh->AddVertexData( 1,  1, 0, 1, 0, Color(0, 1.0f, 0, 1.0f));
	mesh->AddVertexData( 1, -1, 0, 1, 1, Color(0, 0, 1.0f, 1.0f));
	mesh->AddVertexData(-1, -1, 0, 0, 1, Color(1.0f, 0, 0, 1.0f));

	int indexArray[] = { 0, 1, 2, 0, 2, 3};
	//数组直接转vector https://blog.csdn.net/sagittarius_warrior/article/details/54089242
	std::vector<int> index(indexArray, indexArray + sizeof(indexArray) / sizeof(int));
	mesh->indexBuffer = index;
	return mesh;
}

Mesh* Mesh::CreateCube()
{
	Mesh* mesh = new Mesh();
	mesh->AddVertexData(-1.0f, -1.0f, -1.0f,  0.0f,  0.0f);
	mesh->AddVertexData( 1.0f, -1.0f, -1.0f,  1.0f,  0.0f);
	mesh->AddVertexData( 1.0f,  1.0f, -1.0f,  1.0f,  1.0f);
	mesh->AddVertexData( 1.0f,  1.0f, -1.0f,  1.0f,  1.0f);
	mesh->AddVertexData(-1.0f,  1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData(-1.0f, -1.0f, -1.0f,  0.0f,  0.0f);

	mesh->AddVertexData(-1.0f, -1.0f,  1.0f,  0.0f,  0.0f);
	mesh->AddVertexData( 1.0f, -1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData( 1.0f,  1.0f,  1.0f,  1.0f,  1.0f);
	mesh->AddVertexData( 1.0f,  1.0f,  1.0f,  1.0f,  1.0f);
	mesh->AddVertexData(-1.0f,  1.0f,  1.0f,  0.0f,  1.0f);
	mesh->AddVertexData(-1.0f, -1.0f,  1.0f,  0.0f,  0.0f);

	mesh->AddVertexData(-1.0f,  1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData(-1.0f,  1.0f, -1.0f,  1.0f,  1.0f);
	mesh->AddVertexData(-1.0f, -1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData(-1.0f, -1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData(-1.0f, -1.0f,  1.0f,  0.0f,  0.0f);
	mesh->AddVertexData(-1.0f,  1.0f,  1.0f,  1.0f,  0.0f);

	mesh->AddVertexData( 1.0f,  1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData( 1.0f,  1.0f, -1.0f,  1.0f,  1.0f);
	mesh->AddVertexData( 1.0f, -1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData( 1.0f, -1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData( 1.0f, -1.0f,  1.0f,  0.0f,  0.0f);
	mesh->AddVertexData( 1.0f,  1.0f,  1.0f,  1.0f,  0.0f);

	mesh->AddVertexData(-1.0f, -1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData( 1.0f, -1.0f, -1.0f,  1.0f,  1.0f);
	mesh->AddVertexData( 1.0f, -1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData( 1.0f, -1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData(-1.0f, -1.0f,  1.0f,  0.0f,  0.0f);
	mesh->AddVertexData(-1.0f, -1.0f, -1.0f,  0.0f,  1.0f);

	mesh->AddVertexData(-1.0f,  1.0f, -1.0f,  0.0f,  1.0f);
	mesh->AddVertexData( 1.0f,  1.0f, -1.0f,  1.0f,  1.0f);
	mesh->AddVertexData( 1.0f,  1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData( 1.0f,  1.0f,  1.0f,  1.0f,  0.0f);
	mesh->AddVertexData(-1.0f,  1.0f,  1.0f,  0.0f,  0.0f);
	mesh->AddVertexData(-1.0f,  1.0f, -1.0f,  0.0f,  1.0f);
	return mesh;
}

void Mesh::DrawMesh(ApcDevice* device)
{
	//目前假定有IndexBuffer的使用Index
	if (indexBuffer.size() > 0)
		DrawElement(device);
	else
		DrawArray(device);
}

void Mesh::DrawElement(ApcDevice* device)
{
	Matrix mvp = device->GenMVPMatrix();
	for (int i = 0; i < indexBuffer.size(); i = i + 3)
	{
		Vertex p1 = vertexBuffer[indexBuffer[i]];
		Vertex p2 = vertexBuffer[indexBuffer[i + 1]];
		Vertex p3 = vertexBuffer[indexBuffer[i + 2]];
		device->DrawPrimitive(p1, p2, p3, mvp);
	}
}

void Mesh::DrawArray(ApcDevice* device)
{
	Matrix mvp = device->GenMVPMatrix();
	for (int i = 0; i < vertexBuffer.size(); i = i + 3)
	{
		Vertex p1 = vertexBuffer[i];
		Vertex p2 = vertexBuffer[i + 1];
		Vertex p3 = vertexBuffer[i + 2];
		device->DrawPrimitive(p1, p2, p3, mvp);
	}
}

void Mesh::AddVertexData(const Vector3 & pos, float u, float v, const Color& color /* = Color::white */)
{
	Vertex p(pos, color, u, v);
	vertexBuffer.push_back(p);
}

void Mesh::AddVertexData(float posx, float posy, float posz, float u, float v, const Color& color /* = Color::white */)
{
	AddVertexData(Vector3(posx, posy, posz), u, v, color);
}
