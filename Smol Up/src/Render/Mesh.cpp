#include "Mesh.hpp"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vert> buffer, VertexLayout layout)
{
	this->buffer = buffer;
	this->layout = layout;
	
	vbo = VertexBuffer(this->buffer);
	vbo.bind();

	this->layout.bind();
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
	vbo.bind();
	layout.bind();
}

void Mesh::upload()
{
	bind();
	vbo.upload();
}
