#define STB_IMAGE_IMPLEMENTATION

#include "includes.hpp"

static const float TICK_LENGTH = 1.0f / 100.0f;

void error_callback(int error, const char* desc)
{
	fprintf(stderr, "Error: %s\n", desc);
}

//rewriting main to troubleshoot on the fly
int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return -1;

	Window window(1280, 720, "window.");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	//model stuff
	glm::mat4 model_mat(1.0f);
	VertexArray vao;
	VertexBuffer vbo("res/mesh/cub.obj");
	Texture tex("res/texture/wave.png");
	tex.bind(0);
	Shader shader("res/shader/basic.vert", "res/shader/basic.frag");
	shader.bind();
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*(3 + 2 + 3), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*(3 + 2 + 3), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float)*(3 + 2 + 3), (void*)(sizeof(float) * (3 + 2)));
	glEnableVertexAttribArray(2);

	glm::mat4 projection_mat = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);

	auto now = std::chrono::steady_clock::now();
	auto then = now;
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - then).count();
	float timer = 0;
	float tick_timer = 0;

	Camera camera(0, 0, -10, 0, 0, 0);

	glClearColor(0, 0, 0, 1);
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

		vao.bind();
		shader.uniform("model", model_mat, false);
		shader.uniform("view", camera.get_matrix(), false);
		shader.uniform("projection", projection_mat, false);
		glDrawArrays(GL_TRIANGLES, 0, vbo.data.size());

		window.show();

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}