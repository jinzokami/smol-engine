#include "Position.hpp"

Position::Position()
{
}

void Position::translate(f32 dx, f32 dy, f32 dz)
{
	x += dx;
	y += dy;
	z += dz;
}
