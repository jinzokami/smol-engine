#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct Model {
public:
	Model();
	Model(Mesh* mesh, Shader* shader, std::vector<Texture*> textures);
	~Model();

	void bind();

	Mesh* mesh;
	Shader* shader;
	std::vector<Texture*> textures;

	float alpha = 1.0f;

protected:
private:
};