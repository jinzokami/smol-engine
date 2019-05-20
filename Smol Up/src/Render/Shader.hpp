#pragma once

#include <GLM\glm.hpp>

#include "RenderUtil.hpp"

class Shader
{
public:
	Shader();
	Shader(const char * vert_path, const char* frag_path);
	~Shader();

	void bind();

	void attach(GLuint shader);
	void link();

	void uniform(const char * uni, float x);
	void uniform(const char * uni, float x, float y);
	void uniform(const char * uni, float x, float y, float z);
	void uniform(const char * uni, float x, float y, float z, float w);
	void uniform(const char * uni, glm::mat4 mat, bool transpose);

protected:

private:
	GLuint program = 0;

	void uniform(int location, float x);
	void uniform(int location, float x, float y);
	void uniform(int location, float x, float y, float z);
	void uniform(int location, float x, float y, float z, float w);
	void uniform(int location, glm::mat4 mat, bool transpose);
};