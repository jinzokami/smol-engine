#pragma once

#include "Shader.hpp"
#include "Texture.hpp"

struct Material {
public:
	Material();
	Material(Shader shader);
	Material(Shader shader, Texture texture[4]);
	~Material();

	void bind();

	Shader shader;//eventually pointer
	Texture texture[4];//eventually pointers
	/*
	eventually replace this with Texture** texture; int texture_count;
	for now, we have no need for many textures and max in ES is 8, i think.
	*/
protected:
private:
};