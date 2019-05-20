#pragma once

#include "RenderUtil.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();

	GLuint id = 0;
};

