#include "Mesh.hpp"

Mesh::Mesh(std::vector<Vert> verts)
{
	glGenBuffers(1, &vbo);
	this->verts = verts;
}

Mesh::Mesh(std::vector<Vert> verts, std::vector<u32> index)
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	this->verts = verts;
	this->indices = index;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &vbo);
	if (indices.data())
	{
		glDeleteBuffers(1, &ibo);
	}
}

void Mesh::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void Mesh::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::upload()
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert)*verts.size(), &verts[0], GL_STATIC_DRAW);
	if (indices.data())
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32)*indices.size(), &indices[0], GL_STATIC_DRAW);
	}
}

void Mesh::render()
{
	if (indices.data())//if data exists in the indices buffer, then to render properly, we have to use glDrawElements instead of glDrawArrays
	{
		glDrawElements(GL_TRIANGLES, indices.size()*(verts.size()/4), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, verts.size());
	}
}

size_t Mesh::size()
{
	return verts.size();
}
