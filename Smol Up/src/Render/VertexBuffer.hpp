#pragma once

#include <vector>

#include "RenderUtil.hpp"

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(std::vector<Vert> verts);
	~VertexBuffer();

	void bind();
	void unbind();

	void upload();

	GLuint id = 0;
	std::vector<Vert> data;
};

