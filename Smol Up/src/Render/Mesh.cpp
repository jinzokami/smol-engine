#include "Mesh.hpp"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vert> buffer, VertexLayout layout) : vao(), vbo(VertexBuffer(buffer)), vlo(layout)
{
}

Mesh::Mesh(std::vector<Vert> buffer, std::vector<int> layout_info) : vao(), vbo(VertexBuffer(buffer)), vlo(layout_info)
{
}

Mesh::Mesh(const char * mesh_file, std::vector<int> layout_info) : vao(), vbo(VertexBuffer(mesh_file)), vlo(layout_info)
{
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
	vao.bind();
}

void Mesh::upload()
{
	bind();
	vbo.upload();
}
