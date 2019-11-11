#include "Camera.hpp"

Camera::Camera()
{
	transform = Transform(Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f));
	perspective = glm::perspective(arith::deg2rad(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

Camera::Camera(f32 x, f32 y, f32 z, f32 pitch, f32 yaw, f32 roll)
{
	transform = Transform(Position(x, y, z), Rotation(pitch, yaw, roll));
}

void Camera::translate(f32 dx, f32 dy, f32 dz)
{
	transform.position.translate(dx, dy, dz);
}

void Camera::rotate(f32 dx, f32 dy, f32 dz)
{
	transform.rotation.rotate(dx, dy, dz);
}

void Camera::track(f32 x, f32 y, f32 z)//oh, boy
{
	//TODO: actually this
}

glm::mat4 Camera::get_matrix()
{
	return transform.get_matrix();
}
