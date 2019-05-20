#pragma once

#include <vector>

#include "RenderUtil.hpp"
#include "VertexLayout.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

struct Mesh {
public:
	Mesh();
	Mesh(std::vector<Vert> buffer, VertexLayout layout);
	~Mesh();

	void bind();

	void upload();

	std::vector<Vert> buffer;
	VertexBuffer vbo;
	VertexLayout layout;

protected:
private:
};