/*******************************************************************
 * \file Texture.h
 *
 * \author puppet_master
 * \date 2018.5.20ÃÌº”◊¢ Õ
 * \https://blog.csdn.net/puppet_master
 * Texture¿‡
 *******************************************************************/
#pragma once
#include "Color.h"

class Color;
class Texture
{
private:
	int width;
	int height;
	Color textureData[1024][1024];
public:
	Texture();
	~Texture();

	void LoadTexture(const char* path);
	Color Sample(float u, float v);
	float Clamp(float min, float max, float value);
};

