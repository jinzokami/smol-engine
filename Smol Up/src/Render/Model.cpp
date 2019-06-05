#include "Model.hpp"

Model::Model()
{}

Model::Model(Mesh* mesh, Shader* shader, std::vector<Texture*> textures) : mesh(mesh), shader(shader), textures(textures)
{}

Model::~Model()
{}

void Model::bind()
{
	mesh->bind();
	shader->bind();
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->bind(i);
	}
}
