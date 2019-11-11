#pragma once

#include <GLM\glm.hpp>
#include <unordered_map>

#include "RenderUtil.hpp"

class Shader
{
public:
	Shader();
	Shader(const char * vert_path, const char* frag_path);
	~Shader();

	void clean();

	void bind();

	void attach(GLuint shader);
	void link();

	void uniform(const char * uni, float x);
	void uniform(const char * uni, float x, float y);
	void uniform(const char * uni, float x, float y, float z);
	void uniform(const char * uni, float x, float y, float z, float w);
	void uniform(const char * uni, Vec2 vec);
	void uniform(const char * uni, Vec3 vec);
	void uniform(const char * uni, Vec4 vec);
	void uniform(const char * uni, glm::mat4 mat, bool transpose);

protected:

private:
	GLuint id = 0;

	std::unordered_map<std::string, int> uniform_locations;

	void uniform(int location, float x);
	void uniform(int location, float x, float y);
	void uniform(int location, float x, float y, float z);
	void uniform(int location, float x, float y, float z, float w);
	void uniform(int location, glm::mat4 mat, bool transpose);
	int uniform_location(const char* name);
};