#pragma once

#include <cstdint>

namespace arith
{
	namespace rand {
		static struct state32
		{
			uint32_t a, b, c, d; //WARNING: init so not all zeroes on boot.
			uint32_t counter;
		} prng_state32;

		static struct state64
		{
			uint64_t a, b, c, d; //WARNING: init so not all zeroes on boot.
			uint64_t counter;
		} prng_state64;

		uint64_t rand();
		uint64_t xorshift64();
		uint64_t xorshift64star();//WARNING: a must never be zero.
		uint64_t xorwow32();
	};
};