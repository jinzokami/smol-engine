#pragma once

#include "glad.h"
#include "RenderUtil.hpp"
#include <vector>

//Meshes are a fancy abstraction for VBOs, the goal here is to allow for procmeshes
//Meshes attach to renderers, with are abstractions for VAOs and allow for interchangeable shaders
class Mesh
{
public:
	Mesh(std::vector<Vert> verts);
	Mesh(std::vector<Vert> verts, std::vector<u32> index);
	~Mesh();

	void bind();
	void unbind();
	void upload();
	void render();

	size_t size();

	std::vector<Vert> verts;
protected:
private:
	GLuint vbo;
	GLuint ibo = 0;//optional: render function depends on this not being 0, if it is, then the default is set
	
	std::vector<u32> indices;//optional: render function depends on whether this exists
};