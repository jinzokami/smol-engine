#include "Window.hpp"

Window::Window(int width, int height, const char* title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

	window = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwSetKeyCallback(window, key_callback);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

void Window::show()
{
	glfwSwapBuffers(window);
}

bool Window::should_close()
{
	return glfwWindowShouldClose(window);
}

GLFWwindow * Window::get_ref()
{
	return window;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}