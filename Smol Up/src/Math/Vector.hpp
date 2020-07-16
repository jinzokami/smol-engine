#pragma once

#include "../typedefs.hpp"

template<size_t N, typename T>
class Vector
{
public:
	Vector(const T* elm);

	Vector add(const Vector<N, T>& dt);
	Vector sub(const Vector<N, T>& dt);
	Vector neg();
	T dot(const Vector& vec);

	Vector operator+(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator-();
	T& operator[](size_t index);

	T elm[N];
};

template<typename T>
class Vector<4, T>
{
public:
	Vector(T x, T y, T z, T w)
	{
		elm[0] = x;
		elm[1] = y;
		elm[2] = z;
		elm[3] = w;
	}

	Vector(const T* elm);
	Vector add(const Vector<4, T>& dt);
	Vector sub(const Vector<4, T>& dt);
	Vector neg();
	T dot(const Vector& vec);

	Vector operator+(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator-();
	T& operator[](size_t index);

	T elm[4];
};

template<typename T>
class Vector<3, T>
{
public:
	Vector(T x, T y, T z)
	{
		elm[0] = x;
		elm[1] = y;
		elm[2] = z;
	}

	inline Vector cross(const Vector<3, T> & rhs)
	{
		return Vector<3, T>(
			this->elm[1] * rhs.elm[2] - this->elm[2] * rhs.elm[1],
			this->elm[2] * rhs.elm[0] - this->elm[0] * rhs.elm[2],
			this->elm[0] * rhs.elm[1] - this->elm[1] * rhs.elm[0]
			);
	}

	Vector(const T* elm);

	Vector add(const Vector<3, T>& dt);
	Vector sub(const Vector<3, T>& dt);
	Vector neg();
	T dot(const Vector& vec);

	Vector operator+(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator-();
	T& operator[](size_t index);

	T elm[3];
};

template<typename T>
class Vector<2, T>
{
public:
	Vector(T x, T y)
	{
		elm[0] = x;
		elm[1] = y;
	}

	Vector(const T* elm);
	Vector add(const Vector<2, T>& dt);
	Vector sub(const Vector<2, T>& dt);
	Vector neg();
	T dot(const Vector& vec);

	Vector operator+(const Vector& rhs);
	Vector operator-(const Vector& rhs);
	Vector operator-();
	T& operator[](size_t index);

	T elm[2];
};

template<size_t N, typename T>
inline Vector<N, T> operator*(const float& scalar, const Vector<N, T>& vector)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = vector.elm[i] * scalar;
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
inline Vector<N, T> operator*(const Vector<N, T> & vector, const float& scalar)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = vector.elm[i] * scalar;
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
inline Vector<N, T> operator/(const float& scalar, const Vector<N, T>& vector)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = scalar / vector.elm[i];
	}
	return Vector<N, T>(out);
}

template<size_t N, typename T>
inline Vector<N, T> operator/(const Vector<N, T>& vector, const float& scalar)
{
	T out[N];
	for (size_t i = 0; i < N; i++)
	{
		out[i] = vector.elm[i] / scalar;
	}
	return Vector<N, T>(out);
}

//TODO: specialize these operators for dim = 2, 3, 4

//TODO: specialize the add, sub, neg, and dot functions as well

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