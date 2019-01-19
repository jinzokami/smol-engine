#include "Texture.hpp"
#include "stdio.h"

Texture::Texture(Image img)
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

Texture::Texture(const char * path)
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

	printf("Texture Loaded: %s\n\tWidth: %d\n\tHeight: %d\n", path, width, height);
}

Texture::~Texture()
{
	delete image.pixels;
}

void Texture::upload()
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width, image.height, 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixels);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Pixel Texture::get_pixel(u32 x, u32 y)
{
	return image.pixels[x + (y * image.width)];
}

void Texture::set_pixel(u32 x, u32 y, u8 r, u8 g, u8 b)
{
	image.pixels[x + ( y * image.width )] = { r, g, b, 255 };
}
