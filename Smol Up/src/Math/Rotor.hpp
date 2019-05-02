#pragma once
class Rotor
{
public:
	Rotor();
	Rotor(float a, float xy, float xz, float yz);
	~Rotor();

	float a, xy, xz, yz;
};

