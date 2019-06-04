#include "Arith.hpp"

//uses only the first state variable.
uint64_t arith::rand::rand()
{
	return xorshift64();
}

uint64_t arith::rand::xorshift64()
{
	uint64_t x = prng_state64.a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	prng_state64.a = x;
	return x;
}

uint64_t arith::rand::xorshift64star()
{
	uint64_t x = prng_state64.a;
	x ^= x << 12;
	x ^= x >> 25;
	x ^= x << 27;
	prng_state64.a = x;
	return x * 0x2545F4914F6CDD1D;
}

uint64_t arith::rand::xorwow32()
{
	uint32_t t = prng_state32.d;

	uint32_t const s = prng_state32.a;
	prng_state32.d = prng_state32.c;
	prng_state32.c = prng_state32.b;
	prng_state32.b = s;

	t ^= t >> 2;
	t ^= t << 1;
	t ^= s ^ (s << 4);

	prng_state32.a = t;

	prng_state32.counter += 362437;

	return t + prng_state32.counter;
}