#include "Texture.hpp"
#include "stdio.h"

Texture::Texture()
{
	construct("res/texture/error.bmp");
}

Texture::Texture(Image img)
{
	construct(img);
}

Texture::Texture(const char * path)
{
	construct(path);
}

Texture::~Texture()
{}

void Texture::construct(Image img)
{
	//generate and bind texture. save id
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	//set params for textures, same for everone for now
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//upload image data.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width, img.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.pixels);

	//unbind texture.
	glBindTexture(GL_TEXTURE_2D, 0);

	//save image data for reupload.
	image = img;
}

void Texture::construct(const char * path)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, channels;
	unsigned char* pixels = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glBindTexture(GL_TEXTURE_2D, 0);
	image = { width, height, channels, (Pixel *)pixels };

	printf("Texture Loaded: \"%s\"\nWidth: %d\nHeight: %d\n", path, width, height);
}

void Texture::upload()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
}

//bind or rebind a texture
void Texture::bind(int slot)
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id);
	bound_slot = slot;
}

Pixel Texture::get_pixel(u32 x, u32 y)
{
	return image.pixels[x + (y * image.width)];
}

void Texture::set_pixel(u32 x, u32 y, u8 r, u8 g, u8 b)
{
	image.pixels[x + ( y * image.width )] = { r, g, b, 255 };
}
