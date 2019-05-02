#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vert> verts, std::vector<int> layout, Shader shader)
{
	vbo = VertexBuffer(verts);
	vbo.bind();
	this->layout = VertexLayout(layout);
	this->shader = shader;
}

Mesh::~Mesh()
{
}

void Mesh::bind()
{
	vao.bind();
	vbo.bind();
	layout.bind();
	shader.bind();
}

void Mesh::unbind()
{
	vao.unbind();
	vbo.unbind();
	layout.unbind();
	shader.unbind();
}

void Mesh::upload()
{
	vbo.upload();
}

//maybe this should be when the shader gets uniforms uploaded?
void Mesh::render()
{
	glDrawArrays(GL_TRIANGLES, 0, vbo.data.size());
}

size_t Mesh::size()
{
	return vbo.data.size();
}
