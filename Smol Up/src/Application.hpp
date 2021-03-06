#pragma once

#include "includes.hpp"

#define APP_MESH_PATH "res/mesh/"
#define APP_SHADER_PATH "res/shader/"
#define APP_TEXTURE_PATH "res/texture/"

class Application
{
public:
	Application();

	//release textures, meshes, shaders
	~Application();

	void start();
	void run(); //update render loop
	void stop();

	void clean();

	Window window;
	Camera camera;
	Input input;

	Mesh* load_mesh(const char* filename, std::vector<int> layout);
	Texture* load_texture(const char* filename);
	Shader* load_shader(const char* filename);
	Model* load_model(const char* filename);

	std::unordered_map<std::string, Texture> texture_ids;
	std::unordered_map<std::string, Mesh> mesh_ids;
	std::unordered_map<std::string, Shader> shader_ids;
	std::unordered_map<std::string, Model> model_ids;

	//test stuff, delete. maybe
	std::vector<Model*> models;
	std::vector<glm::mat4> mats;
protected:
private:
};