#pragma once

#include "RenderUtil.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();
	void unbind();

	GLuint id = 0;
};

