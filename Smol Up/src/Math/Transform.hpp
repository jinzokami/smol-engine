#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Vector.hpp"
#include "Quaternion.hpp"

class Transform
{
public:
	vec3f position;
	Quaternion orientation;

	vec3f get_forward();
	vec3f get_backward();
	vec3f get_left();
	vec3f get_right();
	vec3f get_up();
	vec3f get_down();

	Transform();
	Transform(vec3f position, Quaternion orientation) : position(position), orientation(orientation) {}

	glm::mat4 get_matrix();

	vec3f get_position();
	Quaternion get_orientation();
};