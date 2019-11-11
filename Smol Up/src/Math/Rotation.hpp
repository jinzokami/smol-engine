#include <GLM\glm.hpp>
#include <GLM\gtc\matrix_transform.hpp>

#include "../Util.hpp"

class Rotation
{
public:
	//euler angles, yes.
	f32 pitch, yaw, roll;

	Rotation();
	Rotation(f32 pitch, f32 yaw, f32 roll) : pitch(pitch), yaw(yaw), roll(roll) {}

	void rotate(f32 dx, f32 dy, f32 dz);
	void set_rotation(f32 dx, f32 dy, f32 dz);

	void add_yaw(f32 da);
	void add_pitch(f32 da);
	void add_roll(f32 da);

	void set_yaw(f32 da);
	void set_pitch(f32 da);
	void set_roll(f32 da);

	glm::mat4 get_matrix();
};