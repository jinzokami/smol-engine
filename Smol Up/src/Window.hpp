#pragma once

#include "GLFW/glfw3.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Window
{
public:
	Window();
	Window(int width, int height, const char* title);
	~Window();

	void show();
	bool should_close();
	void clean();

	GLFWwindow* get_ref();

protected:
private:
	GLFWwindow* window;

	
};