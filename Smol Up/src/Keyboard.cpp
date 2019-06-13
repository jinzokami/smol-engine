#include "Keyboard.hpp"

void Keyboard::update()
{
	for (auto elm : key_state)
	{
		key_state[elm.first].pressed = false;
		key_state[elm.first].released = false;
	}
}

void Keyboard::press(int key)
{
	key_state[key].down = true;
	key_state[key].pressed = true;
}

void Keyboard::release(int key)
{
	key_state[key].down = false;
	key_state[key].released = true;
}

bool Keyboard::is_down(int key)
{
	if (key_state.find(key) != key_state.end())
	{
		return key_state[key].down;
	}
	return false;
}

bool Keyboard::is_pressed(int key)
{
	if (key_state.find(key) != key_state.end())
	{
		return key_state[key].pressed;
	}
	return false;
}

bool Keyboard::is_released(int key)
{
	if (key_state.find(key) != key_state.end())
	{
		return key_state[key].released;
	}
	return false;
}
