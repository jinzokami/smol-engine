#include "Camera.hpp"

Camera::Camera()
{
	transform = Transform(vec3f(0.0f, 0.0f, 0.0f), Quaternion());
	perspective = glm::perspective(arith::degrees_to_radians(60.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

Camera::Camera(f32 x, f32 y, f32 z, f32 pitch, f32 yaw, f32 roll)
{
	//TODO: Quaternion
	transform = Transform(vec3f(x, y, z), Quaternion());
}

void Camera::translate(f32 dx, f32 dy, f32 dz)
{
	//TODO: this
}

void Camera::rotate(f32 dx, f32 dy, f32 dz)
{
	//TODO: this
}

void Camera::track(f32 x, f32 y, f32 z)//oh, boy
{
	//TODO: actually this
}

glm::mat4 Camera::get_matrix()
{
	return transform.get_matrix();
}
