#include "Rotor.hpp"

Rotor::Rotor()
{
	this->a = 0;
	this->xy = 0;
	this->xz = 0;
	this->yz = 0;
}

Rotor::Rotor(float a, float xy, float xz, float yz)
{
	this->a = a;
	this->xy = xy;
	this->xz = xz;
	this->yz = yz;
}


Rotor::~Rotor()
{
}
