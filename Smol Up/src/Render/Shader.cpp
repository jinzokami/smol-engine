#include "Shader.hpp"

Shader::Shader()
{
	GLuint vertex = load_shader("res/shader/basic.vert", GL_VERTEX_SHADER);
	GLuint fragment = load_shader("res/shader/basic.frag", GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	GLint isLinked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char infoLog[512];
		glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		// The program is useless now. So delete it.
		glDeleteProgram(id);

		printf("%s", infoLog);
	}
}

Shader::Shader(const char * vert_path, const char* frag_path)
{
	GLuint vertex = load_shader(vert_path, GL_VERTEX_SHADER);
	GLuint fragment = load_shader(frag_path, GL_FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	GLint isLinked = 0;
	glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char infoLog[512];
		glGetProgramInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		// The program is useless now. So delete it.
		glDeleteProgram(id);

		printf("%s", infoLog);
	}
}

Shader::~Shader()
{
}

void Shader::clean()
{
	glDeleteProgram(id);
}

void Shader::bind()
{
	glUseProgram(id);
}

void Shader::attach(GLuint shader)
{
	glAttachShader(id, shader);
}

void Shader::link()
{
	glLinkProgram(id);
}

void Shader::uniform(int location, float x)
{
	glUniform1f(location, x);
}

void Shader::uniform(int location, float x, float y)
{
	glUniform2f(location, x, y);
}

void Shader::uniform(int location, float x, float y, float z)
{
	glUniform3f(location, x, y, z);
}

void Shader::uniform(int location, float x, float y, float z, float w)
{
	glUniform4f(location, x, y, z, w);
}

void Shader::uniform(int location, glm::mat4 mat, bool transpose)
{
	glUniformMatrix4fv(location, 1, transpose, &mat[0][0]);
}

int Shader::uniform_location(const char * name)
{
	if (uniform_locations.find(name) != uniform_locations.end())
	{
		return uniform_locations[name];
	}

	int loc = glGetUniformLocation(id, name);
	uniform_locations[name] = loc;
	return loc;
}

void Shader::uniform(const char * uni, float x)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, x);
}

void Shader::uniform(const char * uni, float x, float y)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, x, y);
}

void Shader::uniform(const char * uni, float x, float y, float z)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, x, y, z);
}

void Shader::uniform(const char * uni, float x, float y, float z, float w)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, x, y, z, w);
}

void Shader::uniform(const char * uni, Vec2 vec)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, vec.x, vec.y);
}

void Shader::uniform(const char * uni, Vec3 vec)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, vec.x, vec.y, vec.z);
}

void Shader::uniform(const char * uni, Vec4 vec)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, vec.x, vec.y, vec.z, vec.w);
}

void Shader::uniform(const char * uni, glm::mat4 mat, bool transpose)
{
	GLint loc = uniform_location(uni);
	if (loc >= 0)
		uniform(loc, mat, transpose);
}
