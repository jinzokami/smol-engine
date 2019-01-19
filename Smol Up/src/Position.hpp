#include "Util.hpp"

class Position
{
public:
	f32 x, y, z;
	Position();
	Position(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

	void translate(f32 dx, f32 dy, f32 dz);
};