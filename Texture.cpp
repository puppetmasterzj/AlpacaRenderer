#include "Texture.h"
#include "Stdfx.h"


Texture::Texture()
{
	width = 512;
	height = 512;
}


Texture::~Texture()
{
}

void Texture::LoadTexture(const char* path)
{
	HBITMAP bitmap = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	
	HDC hdc = CreateCompatibleDC(NULL);
	SelectObject(hdc, bitmap);
	
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			COLORREF color = GetPixel(hdc, i, j);
			int r = color % 256;
			int g = (color >> 8) % 256;
			int b = (color >> 16) % 256;
			Color c((float)r / 256, (float)g / 256, (float)b / 256, 1);
			textureData[i][j] = c;
		}
	}
}

Color Texture::Sample(float u, float v)
{
	int intu = width * u;
	int intv = height * v;
	return textureData[intu][intv];
}
