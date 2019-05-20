#define STB_IMAGE_IMPLEMENTATION

#include "includes.hpp"

static const float TICK_LENGTH = 1.0f / 100.0f;

void error_callback(int error, const char* desc)
{
	fprintf(stderr, "Error: %s\n", desc);
}

//TODO: add keyboard input and polling
//TODO: Start work on the entity system and figure out what kind of game we'll make with this.
//TODO: Start standardizing uniforms, timers, textures, matrices
//TODO: Memory leak from Image loading, pls fix
//TODO: Video Memory leak from Texture loading, pls fix

int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return -1;

	Window window(1280, 720, "window.");

	//maybe move this into window?
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	glm::mat4 model_mat(1.0f);
	Mesh mesh("res/mesh/cub.obj", {3, 2, 3});
	std::vector<Texture> tex = { Texture("res/texture/wave.png") };
	Material material(Shader("res/shader/basic.vert", "res/shader/basic.frag"), tex);
	Model model(mesh, material);

	glm::mat4 model_mat2(1.0f);
	model_mat2[3][0] = -5;
	Mesh mesh2("res/mesh/sphere.obj", { 3, 2, 3 });
	std::vector<Texture> tex2 = { Texture("res/texture/planet.png") };
	Material material2(Shader("res/shader/basic.vert", "res/shader/basic.frag"), tex2);
	Model model2(mesh2, material2);

	glm::mat4 projection_mat = glm::perspective(45.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);

	Camera camera(0, 0, -10, 0, 0, 0);
	glClearColor(0, 0, 0, 1);

	auto now = std::chrono::steady_clock::now();
	auto then = now;
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - then).count();
	float timer = 0;
	float tick_timer = 0;
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
		model.bind();
		model_mat = glm::rotate(model_mat, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		model.material.shader.uniform("model", model_mat, false);
		model.material.shader.uniform("view", camera.get_matrix(), false);
		model.material.shader.uniform("projection", projection_mat, false);
		glDrawArrays(GL_TRIANGLES, 0, model.mesh.vbo.size());

		model2.bind();
		model_mat2 = glm::rotate(model_mat2, -0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		model2.material.shader.uniform("model", model_mat2, false);
		model2.material.shader.uniform("view", camera.get_matrix(), false);
		model2.material.shader.uniform("projection", projection_mat, false);
		glDrawArrays(GL_TRIANGLES, 0, model2.mesh.vbo.size());

		window.show();

		glfwPollEvents();
		gl_errors();
	}

	glfwTerminate();

	return 0;
}