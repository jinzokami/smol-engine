#pragma once

#include "RenderUtil.hpp"

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexLayout.hpp"

#include "Shader.hpp"

class Mesh
{
public:
	Mesh(std::vector<Vert> verts, std::vector<int> layout, Shader shader);
	~Mesh();

	void bind();
	void unbind();
	void upload();
	void render();

	size_t size();

	VertexArray vao;
	VertexBuffer vbo;
	VertexLayout layout;

	Shader shader;
};