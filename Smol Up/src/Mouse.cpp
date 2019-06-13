#include "Mouse.hpp"

void Mouse::update()
{
	for (auto elm : button_state)
	{
		button_state[elm.first].pressed = false;
		button_state[elm.first].released = false;
	}

	//TODO: add mouse position, mouse position delta, and mousewheel delta
}

void Mouse::press(int button)
{
	button_state[button].down = true;
	button_state[button].pressed = true;
}

void Mouse::release(int button)
{
	button_state[button].down = false;
	button_state[button].released = true;
}

bool Mouse::is_down(int button)
{
	if (button_state.find(button) != button_state.end())
	{
		return button_state[button].down;
	}
	return false;
}

bool Mouse::is_pressed(int button)
{
	if (button_state.find(button) != button_state.end())
	{
		return button_state[button].pressed;
	}
	return false;
}

bool Mouse::is_released(int button)
{
	if (button_state.find(button) != button_state.end())
	{
		return button_state[button].released;
	}
	return false;
}
