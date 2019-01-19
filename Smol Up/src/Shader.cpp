#include "Shader.hpp"

Shader::Shader(const char * vert_path, const char* frag_path)
{
	GLuint vertex = load_shader(vert_path, GL_VERTEX_SHADER);
	GLuint fragment = load_shader(frag_path, GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		char infoLog[512];
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// The program is useless now. So delete it.
		glDeleteProgram(program);

		printf("%s", infoLog);
	}
}

Shader::~Shader()
{
}

void Shader::bind()
{
	glUseProgram(program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::attach(GLuint shader)
{
	glAttachShader(program, shader);
}

void Shader::link()
{
	glLinkProgram(program);
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

void Shader::uniform(const char * uni, float x)
{
	GLint loc = glGetUniformLocation(program, uni);
	uniform(loc, x);
}

void Shader::uniform(const char * uni, float x, float y)
{
	GLint loc = glGetUniformLocation(program, uni);
	uniform(loc, x, y);
}

void Shader::uniform(const char * uni, float x, float y, float z)
{
	GLint loc = glGetUniformLocation(program, uni);
	uniform(loc, x, y, z);
}

void Shader::uniform(const char * uni, float x, float y, float z, float w)
{
	GLint loc = glGetUniformLocation(program, uni);
	uniform(loc, x, y, z, w);
}

void Shader::uniform(const char * uni, glm::mat4 mat, bool transpose)
{
	GLint loc = glGetUniformLocation(program, uni);
	uniform(loc, mat, transpose);
}
