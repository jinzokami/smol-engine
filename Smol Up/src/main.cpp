#define STB_IMAGE_IMPLEMENTATION

#include "includes.hpp"

static const float TICK_LENGTH = 1.0f / 100.0f;

void error_callback(int error, const char* desc)
{
	fprintf(stderr, "Error: %s\n", desc);
}

//TODO: add in keyboard input and polling
//TODO: Start work on the entity system and figure out wha kind of game we'll make with this.
//TODO: Start standardizing uniforms, timers, texutres, matrices
//TODO: Memory leak from Image loading, pls fix
//TODO: VertexArrays broke at bind?
int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return -1;

	Window window(1280, 720, "window.");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	//VertexArray vao;

	//mesh setup
	std::vector<Vert> buffer;
	parse_obj("res/mesh/sphere.obj", buffer);
	std::vector<int> layout = { 3, 2, 3 };
	VertexLayout vl(layout);
	Mesh mesh(buffer, vl);
	
	//material setup
	Shader shader("res/shader/basic.vert", "res/shader/basic.frag");
	Texture texture[4] = {
		Texture("res/texture/wave.png"),
		Texture("res/texture/wave.png"),
		Texture("res/texture/wave.png"),
		Texture("res/texture/wave.png")
	};
	Material material(shader, texture);
	
	//model setup
	Model model(mesh, material);

	//VertexBuffer vbo(buffer);
	//vbo.bind();

	//std::vector<int> layout = { 3, 2, 3 };
	//VertexLayout vl(layout);

	//Shader shader("res/basic.vert", "res/basic.frag");
	//shader.bind();
	
	glm::mat4 model_mat(1.0f);
	glm::mat4 projection_mat = glm::perspective(45.0f, 1280.0f/720.0f, 0.1f, 1000.0f);
	
	//Texture texture("res/wave.png");
	//texture.bind(0);
	
	auto now = std::chrono::steady_clock::now();
	auto then = now;
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - then).count();
	float timer = 0;
	float tick_timer = 0;
	
	Camera camera(0, 0, -2, 0, 0, 0);

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

		model_mat = glm::rotate(model_mat, 0.01f, glm::normalize(glm::vec3(1.0f, 0.0f, 0.0f)));
		
		model.bind();

		//upload shader information
		model.material.shader.uniform("col", 1, 1, 1);
		model.material.shader.uniform("model", model_mat, false);
		model.material.shader.uniform("view", camera.get_matrix(), false);
		model.material.shader.uniform("projection", projection_mat, false);

		
		//vbo.unbind();
		glDrawArrays(GL_TRIANGLES, 0, buffer.size());
		model.unbind();

		window.show();

		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}