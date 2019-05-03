#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer()
{
	data = std::vector<Vert>();
}

VertexBuffer::VertexBuffer(std::vector<Vert> verts)
{
	data = verts;
	glGenBuffers(1, &id);
	upload();
}

VertexBuffer::~VertexBuffer()
{
	if (id != 0)
		glDeleteBuffers(1, &id);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::upload()
{
	if (id != 0) 
	{
		bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vert)*data.size(), &data[0], GL_STATIC_DRAW);
		unbind();
	}
}