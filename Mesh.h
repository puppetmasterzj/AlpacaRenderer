/*******************************************************************
 * \file Mesh.h
 *
 * \author puppet_master
 * \date 2018/05/20添加注释
 * \https://blog.csdn.net/puppet_master
 * \Mesh类，封装了三个基本的Mesh，三角形，正方形，正方体，
 * \可以根据Vertex和Index绘制
 *******************************************************************/
#pragma once
#include "Vertex.h"
#include "ApcDevice.h"
#include <vector>

class Mesh
{
private:
	std::vector<Vertex> vertexBuffer;
	std::vector<int> indexBuffer;

	void DrawElement(ApcDevice* device);
	void DrawArray(ApcDevice* device);
public:
	Mesh();
	~Mesh();

	static Mesh* CreateTrangle();
	static Mesh* CreatePlane();
	static Mesh* CreateCube();

	void AddVertexData(const Vector3 & pos, float u, float v, const Color& color = Color::white);
	void AddVertexData(float posx, float posy, float posz, float u, float v, const Color& color = Color::white);

	void DrawMesh(ApcDevice* device);
};

