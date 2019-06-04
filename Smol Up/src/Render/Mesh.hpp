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
	Mesh(std::vector<Vert> buffer, std::vector<int> layout_info);
	Mesh(const char* mesh_file, std::vector<int> layout_info);
	~Mesh();

	void bind();

	void upload();

	void clean();

	//std::vector<Vert> buffer; //procmesh object
	VertexArray vao;
	VertexBuffer vbo;
	VertexLayout vlo;

protected:
private:
};