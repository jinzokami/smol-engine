#pragma once

#include "GLFW/glfw3.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Window
{
public:
	Window(int width, int height, const char* title);
	~Window();

	void show();
	bool should_close();

	GLFWwindow* get_ref();

protected:
private:
	GLFWwindow* window;

	
};