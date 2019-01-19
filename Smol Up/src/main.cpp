#include <cstdio>
#include <iostream>
#include <chrono>

#define STB_IMAGE_IMPLEMENTATION

#include "Util.hpp"
#include "RenderUtil.hpp"

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Window.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Camera.hpp"

#include "Lulz.hpp"

static const float TICK_LENGTH = 1.0f / 100.0f;

static bool wireframe = false;

void error_callback(int error, const char* desc)
{
	fprintf(stderr, "Error: %s\n", desc);
}

/*
TODO: Models seem to load but are not rendering.
*/
int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return -1;

	Window window(640, 480, "window.");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Shader shader("res/basic.vert", "res/basic.frag");
	shader.bind();

	std::vector<Vert> buffer = load_verts_from_file("res/spr.obj");
	Mesh mesh(buffer);
	mesh.upload();

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), (const void *)sizeof(Vec3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), (const void *)(sizeof(Vec3) + sizeof(Vec2)));
	glEnableVertexAttribArray(2);

	glm::mat4 model(1.0f);
	glm::mat4 projection = glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 1000.0f);
	
	Texture texture("res/sprtex.png");
	texture.bind();
	
	gl_errors();

	auto now = std::chrono::steady_clock::now();
	auto then = now;
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - then).count();
	float timer = 0;
	float tick_timer = 0;
	
	Camera camera(0, 0, -5, 0, 0, 0);
	camera.translate(0, 0, 3);

	glClearColor(0.5f, 0.5f, 0.5f, 1);

	while (!window.should_close())
	{
		then = now;
		now = std::chrono::steady_clock::now();
		float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - then).count();
		timer += elapsed;
		tick_timer += elapsed;

		while (tick_timer >= TICK_LENGTH)
		{
			tick_timer -= TICK_LENGTH;
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		model = glm::rotate(model, 0.01f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		

		shader.uniform("col", 1, 1, 1);

		shader.uniform("model", model, false);
		shader.uniform("view", camera.get_matrix(), false);
		shader.uniform("projection", projection, false);

		mesh.render();

		window.show();

		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}