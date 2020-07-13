#pragma once

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
			lhs[1] * rhs[2] - lhs[2] * rhs[1],
			lhs[2] * rhs[0] - lhs[0] * rhs[2],
			lhs[0] * rhs[1] - lhs[1] * rhs[0]
			);
	}

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
class Vector<2, T>
{
public:
	Vector(T x, T y)
	{
		elm[0] = x;
		elm[1] = y;
	}

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

//TODO: specialize the add, sub, neg, and dot functions as well