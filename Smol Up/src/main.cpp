#include "includes.hpp"

static const float TICK_LENGTH = 1.0f / 100.0f;

void error_callback(int error, const char* desc)
{
	fprintf(stderr, "Error: %s\n", desc);
}

//Note: Mesh object broken from vbo bind call?
int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return -1;

	Window window(640, 480, "window.");

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);

	VertexArray vao;

	std::vector<Vert>* buffer = load_verts_from_file("res/spr.obj");//{ {{1, 0, 0}, {1, 0}, {0, 1, 0}}, {{0, 1, 0}, {0, 1}, {0, 1, 0}}, {{1, 1, 0}, {1, 1}, {0, 1, 0}} };

	VertexBuffer vbo(*buffer);
	vbo.bind();

	std::vector<int> layout = { 3, 2, 3 };
	VertexLayout vl(layout);

	Shader shader("res/basic.vert", "res/basic.frag");
	shader.bind();

	//Mesh mesh(buffer, layout, shader);
	
	glm::mat4 model(1.0f);
	glm::mat4 projection = glm::perspective(45.0f, 640.0f/480.0f, 0.1f, 1000.0f);
	
	Texture texture("res/planet.png");
	texture.bind();
	
	auto now = std::chrono::steady_clock::now();
	auto then = now;
	float elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(now - then).count();
	float timer = 0;
	float tick_timer = 0;
	
	Camera camera(0, 0, -5, 0, 0, 0);
	camera.translate(0, 0, 3);

	glClearColor(0.5f, 0.5f, 0.5f, 1);

	gl_errors();
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

		//mesh.bind();
		//mesh.render();
		//mesh.unbind();
		glDrawArrays(GL_TRIANGLES, 0, buffer->size());

		window.show();

		glfwPollEvents();

		gl_errors();
	}

	glfwTerminate();
	
	return 0;
}