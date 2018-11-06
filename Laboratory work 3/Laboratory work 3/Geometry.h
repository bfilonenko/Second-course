#pragma once


#include <cmath>
#include <vector>
#include <iostream>
#include <assert.h>


using namespace std;


template<typename T>
struct Vector2
{
	T x, y;

	Vector2<T>() : x(T()), y(T()) {}

	Vector2<T>(T x, T y) : x(x), y(y) {}

	Vector2<T>(const Vector2<T> &vector) : x(T()), y(T())
	{
		*this = vector;
	}

	Vector2<T> & operator = (const Vector2 &right)
	{
		if (this != &right)
		{
			x = right.x;
			y = right.y;
		}
		return *this;
	}

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
		return Vector2<T>(T (x * value), T (y * value));
	}

	friend ostream &operator << (ostream &os, Vector2<T> &vector);

	T &operator [] (const int i)
	{
		if (i <= 0)
		{
			return x;
		}
		else
		{
			return y;
		}
	}
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
	T x, y, z;

	Vector3<T>() : x(T()), y(T()), z(T()) {}

	Vector3<T>(T x, T y, T z) : x(x), y(y), z(z) {}

	template<typename U>
	Vector3<T>(const Vector3<U> &right);

	Vector3<T>(const Vector3 &vector) : x(T()), y(T()), z(T())
	{
		*this = vector;
	}

	Vector3<T> & operator = (const Vector3<T> &right)
	{
		if (this != &right)
		{
			x = right.x;
			y = right.y;
			z = right.z;
		}
		return *this;
	}

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

	T &operator [] (const int i)
	{
		if (i <= 0)
		{
			return x;
		}
		else if (i == 1)
		{
			return y;
		}
		else
		{
			return z;
		}
	}
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


template<>
template<>
Vector3<int>::Vector3(const Vector3<float> &vector);

template<>
template<>
Vector3<float>::Vector3(const Vector3<int> &vector);


class Matrix
{
	vector<vector<float> > matrix;

	int rows, cols;

public:
	Matrix(int r = 4, int c = 4);

	inline int getNumberOfRow();
	inline int getNumberOfCol();

	static Matrix identity(int dimensions);

	vector<float> &operator [] (const int i);

	Matrix operator*(const Matrix& right);

	Matrix transpose();

	Matrix inverse();

	friend ostream &operator << (ostream &os, Matrix &m);
};


Vector3float matrixToVector(Matrix matrix);

Matrix vectorToMatrix(Vector3float vector);

Matrix viewport(int x, int y, int width, int height, int depth);