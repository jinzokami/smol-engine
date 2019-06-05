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

void Application::start()
{
	/*
	std::vector<Texture> tex = { load_texture("res/texture/wave.png") };
	glm::mat4 model_mat(1.0f);
	Model model(load_mesh("res/mesh/cub.obj", { 3, 2, 3 }), Material(load_shader("res/shader/basic"), tex));
	models.push_back(model);
	mats.push_back(model_mat);

	std::vector<Texture> tex2 = { load_texture("res/texture/planet.png") };
	glm::mat4 model_mat2(1.0f);
	model_mat2[3][0] = -5;
	Model model2(load_mesh("res/mesh/sphere.obj", { 3, 2, 3 }), Material(load_shader("res/shader/basic"), tex2));
	models.push_back(model2);
	mats.push_back(model_mat2);
	//*/

	models.push_back(load_model("res/asset/sphere.sa"));
	models.push_back(load_model("res/asset/sphere.sa"));
	mats.push_back(glm::mat4(1.0f));
	mats.push_back(glm::mat4(1.0f));
	mats[1][3][0] = -5;
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
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

		//*
		mats[0] = glm::rotate(mats[0], 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		mats[1] = glm::rotate(mats[1], -0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		//*/
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		for (int i = 0; i < models.size(); i++)
		{
			models[i]->bind();
			models[i]->shader->uniform("model", mats[i], false);
			models[i]->shader->uniform("view", camera.get_matrix(), false);
			models[i]->shader->uniform("projection", camera.perspective, false);
			glDrawArrays(GL_TRIANGLES, 0, models[i]->mesh->vbo.size());
		}

		window.show();

		glfwPollEvents();
		gl_errors();
	}
}

void Application::stop()
{
}

//loads a mesh from disk and caches it
Mesh* Application::load_mesh(const char* filename, std::vector<int> layout)
{
	if (mesh_ids.find(filename) != mesh_ids.end())
	{
		return &mesh_ids[filename];
	}
	Mesh mesh(filename, layout);
	mesh_ids[filename] = mesh;
	return &mesh_ids[filename];
}

//loads a texture from disk and caches it
Texture* Application::load_texture(const char* filename)
{
	if (texture_ids.find(filename) != texture_ids.end())
	{
		return &texture_ids[filename];
	}
	Texture tex(filename);
	texture_ids[filename] = tex;
	return &texture_ids[filename];
}

//loads shader files from disk and chaches them
Shader* Application::load_shader(const char* filename)
{
	if (shader_ids.find(filename) != shader_ids.end())
	{
		return &shader_ids[filename];
	}
	std::string path(filename);
	std::string path_vert(path); path_vert.append(".vert");
	std::string path_frag(path); path_frag.append(".frag");
	Shader shader(path_vert.c_str(), path_frag.c_str());
	shader_ids[filename] = shader;
	return &shader_ids[filename];
}

//loads a model from an asset file
Model* Application::load_model(const char* filename)
{
	if (model_ids.find(filename) != model_ids.end())
	{
		return &model_ids[filename];
	}
	std::string model_file = load_ascii(filename);
	std::istringstream model_stream(model_file);

	std::string mesh_path = "res/mesh/";
	std::string shader_path = "res/shader/";
	std::vector<std::string> texture_paths;

	while (!model_stream.eof())
	{
		std::string line;
		char type[256] = { 0 };
		char name[256] = { 0 };
		std::getline(model_stream, line);
		sscanf(line.c_str(), "%s = %s", &type, &name);

		if (strcmp(type, "type") == 0)//make sure we've got a model incoming
		{
			if (strcmp(name, "model") != 0)
			{
				return nullptr;
			}
		}
		else if (strcmp(type, "mesh") == 0)//load the mesh
		{
			std::string nmstr(name);
			mesh_path.append(nmstr);

		}
		else if (strcmp(type, "shader") == 0)//load the shader
		{
			std::string nmstr(name);
			shader_path.append(nmstr);
		}
		else if (strncmp(type, "texture", 8) == 0)//load every present texture
		{
			std::string nmstr(name);
			std::string path = "res/texture/";
			texture_paths.push_back(path.append(nmstr));
		}
	}

	std::vector<Texture*> textures;
	for (int i = 0; i < texture_paths.size(); i++)
	{
		textures.push_back(load_texture(texture_paths[i].c_str()));
	}
	model_ids[filename] = Model(load_mesh(mesh_path.c_str(), { 3, 2, 3 }), load_shader(shader_path.c_str()), textures);
	return &model_ids[filename];
}

//TODO: add keyboard input and polling
//TODO: Start work on the entity system and figure out what kind of game we'll make with this.
//TODO: Start standardizing uniforms, timers, textures, matrices
//TODO: Video Memory leak from Image loading, pls fix
//TODO: Video Memory leak from Texture loading, pls fix
//TODO: Video Memory leak from mesh loading, pls fix
//TODO: Texture loading broken from one line asset loader.
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