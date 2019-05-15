#include "Mesh.hpp"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vert> buffer, VertexLayout layout)
{
	this->buffer = buffer;
	this->layout = layout;

	vao = VertexArray();
	vao.bind();
	

	vbo = VertexBuffer(this->buffer);
	vbo.bind();
	

	this->layout.bind();
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
	vao.bind();
	vbo.bind();
	layout.bind();
}

void Mesh::unbind()
{
	vao.unbind();
	vbo.unbind();
	layout.unbind();
}

void Mesh::upload()
{
	bind();
	vbo.upload();
	unbind();
}
