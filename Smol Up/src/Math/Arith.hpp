#pragma once

#include <cstdint>

#include "Vector.hpp"

#include "ArithOps.hpp"

//useful typedefs
typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef float f32;
typedef double f64;

typedef Vector<2, i32> vec2i;
typedef Vector<3, i32> vec3i;
typedef Vector<4, i32> vec4i;

typedef Vector<2, u32> vec2u;
typedef Vector<3, u32> vec3u;
typedef Vector<4, u32> vec4u;

typedef Vector<2, f32> vec2f;
typedef Vector<3, f32> vec3f;
typedef Vector<4, f32> vec4f;

typedef Vector<2, f64> vec2f64;
typedef Vector<3, f64> vec3f64;
typedef Vector<4, f64> vec4f64;

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