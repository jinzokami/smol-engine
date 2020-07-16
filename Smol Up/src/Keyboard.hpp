#pragma once

#include <unordered_map>

#include <GLFW/glfw3.h>

struct KeyState
{
	bool down, pressed, released;
};

class Keyboard
{
public:
	void update();

	void press(int key);
	void release(int key);

	//returns true if key is being held down
	bool is_down(int key);

	//returns true only if key was pressed in the current frame
	bool is_pressed(int key);

	//returns true only if key was released in the current frame
	bool is_released(int key);

	std::unordered_map<int, KeyState> key_state;
};

namespace kb
{
	std::string key_name(int key);
}