#include "VertexArray.hpp"

/*
input: a list of ints indicating the size of the attribute in floats
*/
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

VertexArray::~VertexArray()
{
}

void VertexArray::bind()
{
	glBindVertexArray(id);
}

void VertexArray::clean()
{
	glDeleteVertexArrays(1, &id);
}
