#pragma once

#include "RenderUtil.hpp"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void bind();

	void clean();

	GLuint id = 0;
};

