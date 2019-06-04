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

VertexBuffer::VertexBuffer(const char * filename)
{
	parse_obj(filename, data);
	glGenBuffers(1, &id);
	upload();
}

VertexBuffer::~VertexBuffer()
{
	
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::upload()
{
	if (id != 0) 
	{
		if (data.size() == 0)
		{
			printf("VBO has no data.\n");
			return;
		}
		bind();
		vert_count = data.size();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vert)*data.size(), &data[0], GL_STATIC_DRAW);
	}
}

void VertexBuffer::clean()
{
	if (id != 0)
		glDeleteBuffers(1, &id);
}

int VertexBuffer::size()
{
	return vert_count;
}
