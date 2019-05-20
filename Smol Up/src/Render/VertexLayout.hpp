#pragma once

#include <vector>

#include "RenderUtil.hpp"

class VertexLayout
{
public:

	VertexLayout();
	VertexLayout(std::vector<int> attribs);
	~VertexLayout();

	void bind();

	std::vector<int> attribs;
};