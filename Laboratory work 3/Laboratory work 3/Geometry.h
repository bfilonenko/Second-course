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
			T x, y;
		};

		T raw[2];
	};

	Vector2() : x(0), y(0) {}

	Vector2(T x, T y) : x(x), y(y) {}

	inline Vector2<T> operator + (const Vector2<T> &right) const
	{
		return Vector2<T>(x + right.x, y + right.y);
	}

	inline Vector2<T> operator - (const Vector2<T> &right) const
	{
		return Vector2<T>(x - right.x, y - right.y);
	}

	inline Vector2<T> operator * (float value) const
	{
		return Vector2<T>(x * value, y * value);
	}

	friend ostream &operator << (ostream &os, Vector2<T> &vector);

};


template <typename T>
ostream &operator << (ostream &os, Vector2<T> &vector)
{
	os << "(" << vector.x << ", " << vector.y << ")\n";
	return os;
}


template<typename T>
struct Vector3
{
	union
	{
		struct
		{
			T x, y, z;
		};

		T raw[3];
	};

	Vector3() : x(0), y(0), z(0) {}

	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

	inline Vector3<T> operator ^ (const Vector3<T> &right) const
	{
		return Vector3<T>(y * right.z - z * right.y, z * right.x - x * right.z, x * right.y - y * right.x);
	}

	inline Vector3<T> operator + (const Vector3<T> &right) const
	{
		return Vector3<T>(x + right.x, y + right.y, z + right.z);
	}

	inline Vector3<T> operator - (const Vector3<T> &right) const
	{
		return Vector3<T>(x - right.x, y - right.y, z - right.z);
	}

	inline Vector3<T> operator * (float value) const
	{
		return Vector3<T>(x * value, y * value, z * value);
	}

	inline T operator * (const Vector3<T> &right) const
	{
		return x * right.x + y * right.y + z * right.z;
	}

	float norm() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector3<T> normalize(T l = 1)
	{
		*this = (*this) * (l / norm());
		return *this;
	}

	friend ostream &operator << (ostream &os, Vector3<T> &vector);
};


template <typename T>
ostream &operator << (ostream &os, Vector3<T> &vector)
{
	os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")\n";
	return os;
}


typedef Vector2<float> Vector2float;
typedef Vector2<int>   Vector2int;
typedef Vector3<float> Vector3float;
typedef Vector3<int>   Vector3int;