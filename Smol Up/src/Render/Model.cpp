#include "Model.hpp"

Model::Model()
{
}

Model::Model(Mesh &mesh, Material material) : mesh(mesh), material(material)
{
}

Model::~Model()
{
}

void Model::bind()
{
	mesh.bind();
	material.bind();
}
