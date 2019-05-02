#include "Transform.hpp"

Transform::Transform()
{
}

glm::mat4 Transform::get_matrix()
{
	glm::mat4 mat(1.0f);
	
	//maybe reverse order?
	mat = glm::rotate(mat, rotation.yaw, glm::vec3(0, 1, 0));
	mat = glm::rotate(mat, rotation.pitch, glm::vec3(1, 0, 0));
	mat = glm::rotate(mat, rotation.roll, glm::vec3(0, 0, 1));

	//scale here.

	mat = glm::translate(mat, glm::vec3(position.x, position.y, position.z));

	return mat;
}

Position Transform::get_position()
{
	return position;
}

Rotation Transform::get_rotation()
{
	return rotation;
}
