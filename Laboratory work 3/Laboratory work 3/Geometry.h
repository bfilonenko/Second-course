#pragma once


#include <cmath>
#include <iostream>


using namespace std;


template<typename T>
struct Vector2
{
	union
	{
		struct
		{
			T u, v;
		};

		struct
		{
			T x, y;
		};

		T raw[2];
	};

	Vector2() : u(0), v(0) {}

	Vector2(T u, T v) : u(u), v(v) {}

	inline Vector2<T> operator+ (const Vector2<T> &right) const
	{
		return Vector2<T>(u + right.u, v + right.v);
	}

	inline Vector2<T> operator -(const Vec2<t> &right) const
	{
		return Vector2<T>(u - right.u, v - right.v);
	}

	inline Vector2<T> operator *(float value) const
	{
		return Vector2<T>(u * value, v * value);
	}

	friend ostream &operator << (ostream& os, Vector2<T> &vector);

};


template <typename T>
ostream &operator << (ostream& os, Vector2<T> &vector)
{
	os << "(" << vector.x << ", " << vector.y << ")\n";
	return s;
}