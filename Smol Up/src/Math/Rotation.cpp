#include "Rotation.hpp"

Rotation::Rotation()
{
}

void Rotation::rotate(f32 dx, f32 dy, f32 dz)
{
	add_pitch(dx);
	add_yaw(dy);
	add_roll(dz);
}

void Rotation::set_rotation(f32 dx, f32 dy, f32 dz)
{
	set_pitch(dx);
	set_yaw(dy);
	set_roll(dz);
}

void Rotation::add_yaw(f32 da)
{
	yaw += da;
}

void Rotation::add_pitch(f32 da)
{
	pitch += da;
}

void Rotation::add_roll(f32 da)
{
	roll += da;
}

void Rotation::set_yaw(f32 da)
{
	yaw = da;
}

void Rotation::set_pitch(f32 da)
{
	pitch = da;
}

void Rotation::set_roll(f32 da)
{
	roll = da;
}

glm::mat4 Rotation::get_matrix()
{
	glm::mat4 mat(1.0f);

	mat = glm::rotate(mat, pitch, glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, yaw, glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, roll, glm::vec3(0, 0, 1));

	return mat;
}
