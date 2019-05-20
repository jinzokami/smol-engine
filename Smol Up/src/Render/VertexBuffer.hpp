#pragma once

#include <vector>

#include "RenderUtil.hpp"

class VertexBuffer
{
public:
	VertexBuffer();
	//load models from vertices
	VertexBuffer(std::vector<Vert> verts);
	//load models directly from files.
	VertexBuffer(const char* filename);
	~VertexBuffer();

	void bind();

	void upload();

	GLuint id = 0;
	std::vector<Vert> data;
};

