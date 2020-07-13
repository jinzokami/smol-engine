#pragma once

#include "../Util.hpp"
#include "Arith.hpp"

class Quaternion
{
public:
	Quaternion() : w(1), i(0), j(0), k(0) {}
	Quaternion(f32 w, f32 i, f32 j, f32 k) : w(w), i(i), j(j), k(k) {}
	Quaternion(vec3f axis, f32 degrees);

	vec3f apply_rotation(vec3f& vec);

	Quaternion operator*(const Quaternion& rhs);

	Quaternion inverse();

	//TODO: matrix conversion

	f32 w, i, j, k;
};

