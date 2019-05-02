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
inline std::vector<Vert>* load_verts_from_file(const char* path)
{
	std::vector<Vec3> verts;
	std::vector<Vec2> uvs;
	std::vector<Vec3> normals;
	std::vector<Face> faces;

	std::vector<Vert>* out_verts = new std::vector<Vert>();

	//TODO: parse each line of the file.
	//depending on the first 1-2 chars the line represents something different.
	//mtllib is supposed to be important, but idgaf
	//o denotes a new object, we'll have to have submeshes within each model.
	//v is a vertex position. they should be loaded in the order they appear.
	//vt is a texture coordinate.
	//vn is a normal, the number of these does not neccessarily correspond
		//to the number of vertices, sometimes it's the number of faces, sometimes it's vertices.
	//no idea what s means (smoothing group, but no idea what THAT means)
	//usemtl is another idgaf
	//blender exports model info in a very specific way:
	//o object_name
	//v x.x y.y z.z
	//...
	//vt u.u v.v
	//...
	//vn x.x y.y z.z
	//...
	//usemtl
	//s ?
	//f v/vt/vn v/vt/vn v/vt/vn
	//...
	//next object or eof
	//
	//the spec seems to assume that data is not thrown out when the next object is loaded.
	//
	//process:
	//parse each line, if line is v, vt, or vn push vec3 or vec2 to appropriate vector
	//if line is f, assemble a trio of verts using the v, vt, vn indices specified by the line.
	//if line is o, create a new mesh named whatever comes after o
	//verts are pushed to the last o created

	
	std::ifstream file(path);
	while (!file.eof())
	{
		std::string buffer;
		std::getline(file, buffer);
		std::stringstream line(buffer);
		//printf("%s\n", buffer);
		std::string token;
		line >> token;
		
		if (token == "v")
		{
			std::string vx, vy, vz;
			line >> vx;
			line >> vy;
			line >> vz;
			Vec3 vec = { std::stof(vx), std::stof(vx), std::stof(vx) };
			verts.push_back(vec);
		}
		else if (token == "vn")
		{
			std::string vx, vy, vz;
			line >> vx;
			line >> vy;
			line >> vz;
			Vec3 vec = { std::stof(vx), std::stof(vx), std::stof(vx) };
			normals.push_back(vec);
		}
		else if (token == "vt")
		{
			std::string vx, vy;
			line >> vx;
			line >> vy;
			Vec2 vec = { std::stof(vx), std::stof(vx) };
			uvs.push_back(vec);
		}
		else if (token == "f")
		{
			Face face;
			std::string v, vn, vt;

			std::getline(line, v , '/');
			std::getline(line, vt, '/');
			std::getline(line, vn, ' ');

			face.vert[0] = std::stoi(v) - 1;
			face.uv[0] = std::stoi(vt) - 1;
			face.normal[0] = std::stoi(vn) - 1;

			std::getline(line, v, '/');
			std::getline(line, vt, '/');
			std::getline(line, vn, ' ');

			face.vert[1] = std::stoi(v) - 1;
			face.uv[1] = std::stoi(vt) - 1;
			face.normal[1] = std::stoi(vn) - 1;

			std::getline(line, v, '/');
			std::getline(line, vt, '/');
			std::getline(line, vn, ' ');

			face.vert[2] = std::stoi(v) - 1;
			face.uv[2] = std::stoi(vt) - 1;
			face.normal[2] = std::stoi(vn) - 1;
			
			printf("v: %s | vt: %s | vn: %s\n", v.c_str(), vt.c_str(), vn.c_str());
			
			faces.push_back(face);
		}
		//TODO: add support for 'o' instructions, and return multiple meshes, one for each 'o'
	}

	for (int i = 0; i < faces.size(); i++)
	{
		out_verts->push_back({ 
			{verts[faces[i].vert[0]].x, verts[faces[i].vert[0]].y, verts[faces[i].vert[0]].z}, 
			{uvs[faces[i].uv[0]].x, uvs[faces[i].uv[0]].y}, 
			{normals[faces[i].normal[0]].x, normals[faces[i].normal[0]].y, normals[faces[i].normal[0]].z}
			});

		out_verts->push_back({
			{verts[faces[i].vert[1]].x, verts[faces[i].vert[1]].y, verts[faces[i].vert[1]].z},
			{uvs[faces[i].uv[1]].x, uvs[faces[i].uv[1]].y},
			{normals[faces[i].normal[1]].x, normals[faces[i].normal[1]].y, normals[faces[i].normal[1]].z}
			});

		out_verts->push_back({
			{verts[faces[i].vert[2]].x, verts[faces[i].vert[2]].y, verts[faces[i].vert[2]].z},
			{uvs[faces[i].uv[2]].x, uvs[faces[i].uv[2]].y},
			{normals[faces[i].normal[2]].x, normals[faces[i].normal[2]].y, normals[faces[i].normal[2]].z}
			});
	}

	return out_verts;
}

//#pragma pack (4)