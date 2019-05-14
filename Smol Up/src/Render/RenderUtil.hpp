#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../GL/glad.h"

#include "../Util.hpp"

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Vert
{
	Vec3 v;
	Vec2 vt;
	Vec3 vn;
};

struct RenderInfo
{
	int loc_vertex, loc_normal, loc_uv; //set to -1 to indicate this element does not exist.
	int size_vertex, size_normal, size_uv; //take care to set to zero if element does not exist.
	GLuint program; //the shader program this information is attached to.
};

inline GLuint load_shader(const char* path, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);

	const char* shader_src = load_ascii(path);
	glShaderSource(shader, 1, &shader_src, NULL);
	glCompileShader(shader);
	delete shader_src;

	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		glGetShaderInfoLog(shader, 512, NULL, buffer);
		printf("%s", buffer);
		return -1;
	}

	return shader;
}

struct Pixel
{
	unsigned char r, g, b, a;
};

struct Image
{
	int width, height, channels;
	Pixel* pixels;
};
/*
#pragma pack (1)
struct BMP_Header
{
	//first 14 bytes let you know this is, in fact a BMP.
	u16 magic;//likely "BM"
	u32 file_size;
	u16 reserved1;
	u16 reserved2;
	u32 pixel_offset;

	//these next bytes give info on how to interpret the pixel data.
	u32 header_size;
	i32 width;
	i32 height;
	i16 planes;
	i16 bit_count;
	u32 compression;
	u32 image_size;
	i32 pixels_per_meter_x;
	i32 pixels_per_meter_y;
	u32 color_used;
	u32 color_important;
};

inline Image load_image(const char * path)
{
	FILE * file;
	fopen_s(&file, path, "rb");

	BMP_Header * pauly = new BMP_Header[1];
	int read_in = fread((void *)(pauly), sizeof(char), 54, file);

	int pix_count = pauly->image_size / 3;
	Pixel * pixels = new Pixel[pix_count];

	switch (pauly->bit_count)
	{
	case 24:
	{
		int pix_ptr = 0;
		while (!feof(file))
		{
			Pixel dummy = { (char)0, (char)0, (char)0, (char)255 };
			fread(&dummy, sizeof(char), 3, file);
			pixels[pix_ptr] = { dummy.b, dummy.g, dummy.r, dummy.a };
			pix_ptr++;
		}
	} break;
	default:
		printf("I don't know what to do with this: bpp = %d\n", pauly->bit_count);
		break;
	}

	Image img;
	img.width = pauly->width;
	img.height = pauly->height;
	img.pixels = pixels;

	return img;
}
*/
inline void gl_errors()
{
	GLenum err = GL_NO_ERROR;

	do
	{
		err = glGetError();
		switch (err)
		{
		case GL_NO_ERROR:
			printf("No Errors, Or Errors Cleared.\n");
			break;
		case GL_INVALID_OPERATION:
			printf("Error: %d, Invalid Operation!\n", err);
			break;
		default:
			printf("Unhandled Error Code: %d\n", err);
			break;
		}
	} while (err != GL_NO_ERROR);
}

struct Face
{
	int vert[3];
	int uv[3];
	int normal[3];
};

//NOTE: exclusively for use with .obj files
//std::vector<Vert> load_verts_from_file(const char* path);
void parse_obj(const char* filename, std::vector<Vert> &buffer);
//#pragma pack (4)