#pragma once

#include "Vector.hpp"

//operator overloads involving two different classes go here.
//operator overloads involving one or more of a single class go in that respective class

template<size_t N, typename T>
inline Vector<N, T> operator*(const float& scalar, const Vector<N, T>& vector)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = this->elm[i] * scalar;
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
inline Vector<N, T> operator*(const Vector<N, T> & vector, const float& scalar)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = this->elm[i] * scalar;
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
inline Vector<N, T> operator/(const float& scalar, const Vector<N, T>& vector)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = scalar / this->elm[i];
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
inline Vector<N, T> operator/(const Vector<N, T>& vector, const float& scalar)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = this->elm[i] / scalar;
	}
	return Vector<N, T>(out);
}

//TODO: specialize these operators for dim = 2, 3, 4