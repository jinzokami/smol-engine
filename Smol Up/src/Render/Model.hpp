#pragma once

#include "Mesh.hpp"
#include "Material.hpp"

struct Model {
public:
	Model(Mesh mesh, Material material);
	~Model();

	void bind();
	void unbind();

	Mesh mesh;
	Material material;
	//Transform
protected:
private:
};