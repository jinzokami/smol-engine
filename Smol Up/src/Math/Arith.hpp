#pragma once

#include <cstdint>

#include "../typedefs.hpp"

constexpr auto PI = 3.1415926535897;

namespace arith
{
	namespace rand {
		static struct state32
		{
			u32 a, b, c, d; //WARNING: init so not all zeroes on boot.
			u32 counter;
		} prng_state32;

		static struct state64
		{
			u64 a, b, c, d; //WARNING: init so not all zeroes on boot.
			u64 counter;
		} prng_state64;

		u64 rand();
		u64 xorshift64();
		u64 xorshift64star();//WARNING: a must never be zero.
		u64 xorwow32();
	};

	inline f32 degrees_to_radians(f32 deg)
	{
		return (deg*PI) / 180.0f;
	}

	inline f32 radians_to_degrees(f32 rad)
	{
		return (rad*180.0f) / PI;
	}
};