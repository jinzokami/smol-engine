#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "Position.hpp"
#include "Rotation.hpp"

class Transform
{
public:
	Position position;
	Rotation rotation;

	Transform();
	Transform(Position position, Rotation rotation) : position(position), rotation(rotation) {}

	glm::mat4 get_matrix();

	Position get_position();
	Rotation get_rotation();
};