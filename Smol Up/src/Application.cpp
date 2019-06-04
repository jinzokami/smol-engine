#define STB_IMAGE_IMPLEMENTATION

#include "Application.hpp"

static const float TICK_LENGTH = 1.0f / 100.0f;

void error_callback(int error, const char* desc)
{
	fprintf(stderr, "Error: %s\n", desc);
}

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}

Application::Application()
{
	window = Window(1280, 720, "window.");

	//maybe move this into window?
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(message_callback, 0);

	gl_errors();
}

Application::~Application()
{}

glm::mat4 model_mat, model_mat2;

void Application::start()
{
	std::vector<Texture> tex = { load_texture("res/texture/wave.png") };
	model_mat = glm::mat4(1.0f);
	Model model(load_mesh("res/mesh/cub.obj", { 3, 2, 3 }), Material(load_shader("res/shader/basic"), tex));
	models.push_back(model);

	std::vector<Texture> tex2 = { load_texture("res/texture/planet.png") };
	model_mat2 = glm::mat4(1.0f);
	model_mat2[3][0] = -5;
	Model model2(load_mesh("res/mesh/sphere.obj", { 3, 2, 3 }), Material(load_shader("res/shader/basic"), tex2));
	models.push_back(model2);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Application::run()
{
	camera.translate(0, 0, -10);
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
		models[0].bind();
		model_mat = glm::rotate(model_mat, 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		models[0].material.shader.uniform("model", model_mat, false);
		models[0].material.shader.uniform("view", camera.get_matrix(), false);
		models[0].material.shader.uniform("projection", camera.perspective, false);
		glDrawArrays(GL_TRIANGLES, 0, models[0].mesh.vbo.size());

		models[1].bind();
		model_mat2 = glm::rotate(model_mat2, -0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		models[1].material.shader.uniform("model", model_mat2, false);
		models[1].material.shader.uniform("view", camera.get_matrix(), false);
		models[1].material.shader.uniform("projection", camera.perspective, false);
		glDrawArrays(GL_TRIANGLES, 0, models[1].mesh.vbo.size());

		window.show();

		glfwPollEvents();
		gl_errors();
	}
}

void Application::stop()
{
}

Mesh Application::load_mesh(const char* filename, std::vector<int> layout)
{
	if (mesh_ids.find(filename) != mesh_ids.end())
	{
		return mesh_ids[filename];
	}
	Mesh mesh(filename, layout);
	mesh_ids[filename] = mesh;
	return mesh;
}

Texture Application::load_texture(const char* filename)
{
	if (texture_ids.find(filename) != texture_ids.end())
	{
		return texture_ids[filename];
	}
	Texture tex(filename);
	texture_ids[filename] = tex;
	return tex;
}

Shader Application::load_shader(const char* filename)
{
	if (shader_ids.find(filename) != shader_ids.end())
	{
		return shader_ids[filename];
	}
	std::string path(filename);
	std::string path_vert(path); path_vert.append(".vert");
	std::string path_frag(path); path_frag.append(".frag");
	Shader shader(path_vert.c_str(), path_frag.c_str());
	shader_ids[filename] = shader;
	return shader;
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
	Application app;
	app.start();
	app.run();
	app.stop();
	
	glfwTerminate();

	return 0;
}