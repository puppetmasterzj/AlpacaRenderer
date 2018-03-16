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
};

