#pragma once

#include "RenderUtil.hpp"

class Texture
{
public:
	Texture();
	Texture(Image img);
	Texture(const char* path);
	~Texture();

	void upload();

	void bind(int slot);

	Pixel get_pixel(u32 x, u32 y);
	void set_pixel(u32 x, u32 y, u8 r, u8 g, u8 b);

	Image image;
	GLuint id = 0;
protected:
private:
	//these exist so i don't have to rewrite default constructor
	void construct(Image img);
	void construct(const char* path);

	int bound_slot = -1;
};