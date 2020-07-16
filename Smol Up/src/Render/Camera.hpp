#pragma once

#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "../Math/Transform.hpp"
#include "../Math/Arith.hpp"

//wraps a Transform. may have extra functionality later.
class Camera
{
public:
	Transform transform;
	
	Camera();
	Camera(f32 x, f32 y, f32 z, f32 pitch, f32 roll, f32 yaw);

	void translate(f32 dx, f32 dy, f32 dz);//translates camera
	void rotate(f32 dx, f32 dy, f32 dz);//rotates camera
	void track(f32 x, f32 y, f32 z);//rotates camera to track position
	
	glm::mat4 get_matrix();
	glm::mat4 perspective;
};