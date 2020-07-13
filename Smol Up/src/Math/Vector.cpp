#include "Vector.hpp"

template<size_t N, typename T>
Vector<N, T>::Vector(const T* elm)
{
	for (size_t i = 0; i < N; i++)
	{
		this->elm[i] = elm[i];
	}
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::add(const Vector<N, T>& dt)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = this->elm[i] + dt[i];
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::sub(const Vector<N, T>& dt)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = this->elm[i] - dt[i];
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
Vector<N, T> Vector<N, T>::neg()
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = -this->elm[i];
	}
	return Vector<N, T>(out);
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator+(const Vector<N, T> & rhs)
{
	return add(rhs.elm);
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-(const Vector<N, T> & rhs)
{
	return sub(rhs.elm);
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator-()
{
	return neg();
}

template <size_t N, typename T>
T& Vector<N, T>::operator[](size_t index)
{
	return elm[index];
}

template <size_t N, typename T>
T Vector<N, T>::dot(const Vector<N, T> & vec)
{
	T out;
	for (size_t i = 0; i < N; i++)
	{
		out[i] += this->elm[i] * dt[i];
	}
	return out;
}
