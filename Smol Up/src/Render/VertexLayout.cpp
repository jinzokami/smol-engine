#include "VertexLayout.hpp"

VertexLayout::VertexLayout()
{
}

VertexLayout::VertexLayout(std::vector<int> attribs)
{
	this->attribs = attribs;
	bind();
}

VertexLayout::~VertexLayout()
{
}

void VertexLayout::bind()
{
	int vert_size = 0;
	for (int i = 0; i < attribs.size(); i++)
	{
		vert_size += attribs[i];
	}

	int off = 0;
	for (int i = 0; i < attribs.size(); i++)
	{
		glVertexAttribPointer((GLuint)i, (GLint)attribs[i], GL_FLOAT, GL_FALSE, (GLsizei)(vert_size * sizeof(float)), (const GLvoid *)(off * sizeof(float)));
		glEnableVertexAttribArray(i);

		off += attribs[i];
	}
}
