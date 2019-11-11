#include "Model.hpp"

Model::Model()
{}

Model::Model(Mesh* mesh, Shader* shader, std::vector<Texture*> textures) : mesh(mesh), shader(shader), textures(textures)
{}

Model::Model(Mesh * mesh, Shader * shader) : mesh(mesh), shader(shader)
{}

Model::~Model()
{}

//no textures bound if none present, write a way to bind default texture if needed
void Model::bind()
{
	mesh->bind();
	shader->bind();
	for (int i = 0; i < textures.size(); i++)
	{
		textures[i]->bind(i);
	}

	shader->uniform("alpha", alpha);
	shader->uniform("color_frag", color);
}
