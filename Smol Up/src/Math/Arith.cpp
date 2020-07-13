#include "Arith.hpp"

//uses only the first state variable.
u64 arith::rand::rand()
{
	return xorshift64();
}

u64 arith::rand::xorshift64()
{
	u64 x = prng_state64.a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	prng_state64.a = x;
	return x;
}

u64 arith::rand::xorshift64star()
{
	u64 x = prng_state64.a;
	x ^= x << 12;
	x ^= x >> 25;
	x ^= x << 27;
	prng_state64.a = x;
	return x * 0x2545F4914F6CDD1D;
}

u64 arith::rand::xorwow32()
{
	u32 t = prng_state32.d;

	u32 const s = prng_state32.a;
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