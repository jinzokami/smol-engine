#pragma once

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

struct Model {
public:
	Model();
	Model(Mesh* mesh, Shader* shader, std::vector<Texture*> textures);
	Model(Mesh* mesh, Shader* shader);
	~Model();

	void bind();

	Mesh* mesh;
	Shader* shader;
	std::vector<Texture*> textures;

	float alpha = 1.0f;
	Vec3 color = {1.0f, 1.0f, 1.0f};

protected:
private:
};