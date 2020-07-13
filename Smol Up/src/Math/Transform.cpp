#include "Transform.hpp"

//TODO: rotate each of these before returning
vec3f Transform::get_forward()
{
	vec3f forward = vec3f(0, 0, 1);
	return forward;
}

vec3f Transform::get_backward()
{
	vec3f backward = vec3f(0, 0, -1);
	return backward;
}

vec3f Transform::get_left()
{
	vec3f left = vec3f(1, 0, 0);
	return left;
}

vec3f Transform::get_right()
{
	vec3f right = vec3f(-1, 0, 0);
	return right;
}

vec3f Transform::get_up()
{
	vec3f up = vec3f(0, -1, 0);
	return up;
}

vec3f Transform::get_down()
{
	vec3f down = vec3f(0, 1, 0);
	return down;
}

Transform::Transform()
{
	this->position = vec3f(0, 0, 0);
}

glm::mat4 Transform::get_matrix()
{
	//TODO: this
}

vec3f Transform::get_position()
{
	return position;
}

Quaternion Transform::get_orientation()
{
	return orientation;
}
