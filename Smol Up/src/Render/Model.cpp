#include "Model.hpp"

Model::Model(Mesh mesh, Material material)
{
	this->mesh = mesh;
	this->material = material;
}

Model::~Model()
{
}

void Model::bind()
{
	mesh.bind();
	material.bind();
}
