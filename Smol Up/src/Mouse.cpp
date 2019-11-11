#include "Mouse.hpp"

void Mouse::update()
{
	//function should run BEFORE glfwPollEvents
	for (auto elm : button_state)
	{
		button_state[elm.first].pressed = false;
		button_state[elm.first].released = false;
	}

	//TODO: add mousewheel delta
	this->last_x = this->x;
	this->last_y = this->y;
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

void Mouse::get_position(float & x, float & y)
{
	x = this->x;
	y = this->y;
}

void Mouse::get_delta(float & dx, float & dy)
{
	dx = this->x - this->last_x;
	dy = this->y - this->last_y;
}

void Mouse::set_position(float x, float y)
{
	this->x = x;
	this->y = y;
}
