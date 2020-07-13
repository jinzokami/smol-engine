#include "Quaternion.hpp"

Quaternion::Quaternion(vec3f axis, f32 degrees)
{
	f32 half_angle = arith::degrees_to_radians(degrees)*0.5;
	vec3f scaled_axis = axis * sin(half_angle);
	f32 scalar = cos(half_angle);
	this->w = scalar;
	this->i = scaled_axis[0];
	this->j = scaled_axis[1];
	this->k = scaled_axis[2];
}

vec3f Quaternion::apply_rotation(vec3f & vec)
{
	Quaternion v = Quaternion(0, vec[0], vec[1], vec[2]);
	Quaternion pvpinv = *this * v * inverse();
	return vec3f(pvpinv.i, pvpinv.j, pvpinv.k);
}

Quaternion Quaternion::operator*(const Quaternion & rhs)
{
	f32 ps = this->w;
	f32 qs = rhs.w;
	vec3f pv = vec3f(this->i, this->j, this->k);
	vec3f qv = vec3f(rhs.i, rhs.j, rhs.k);

	vec3f psqv = ps * qv;
	vec3f qspv = qs * pv;
	vec3f pvqv = pv.cross(qv);

	vec3f ijk = psqv + qspv + pvqv;
	f32 w = ps * qs - pv.dot(qv);

	return Quaternion(w, ijk[0], ijk[1], ijk[2]);
}

Quaternion Quaternion::inverse()
{
	return Quaternion(this->w, -this->i, -this->j, -this->k);
}