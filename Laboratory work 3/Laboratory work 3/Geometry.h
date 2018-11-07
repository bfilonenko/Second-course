#pragma once


#include <cmath>
#include <vector>
#include <iostream>
#include <assert.h>


using namespace std;


template<size_t DimCols, size_t DimRows, typename T>
class Matrix;



template <size_t Dim, typename T>
struct Vector
{
private:
	T data[Dim];

public:
	Vector()
	{
		for (size_t i = Dim; i--; data[i] = T());
	}

	T &operator [] (const size_t i)
	{
		assert(i < Dim);
		
		return data[i];
	}

	const T &operator [] (const size_t i) const
	{
		assert(i < Dim);
		return data[i];
	}
};



template <typename T>
struct Vector<2, T>
{
	T x, y;

	Vector() : x(T()), y(T())
	{

	}

	Vector(T x, T y) : x(x), y(y)
	{

	}

	template <class U>
	Vector<2, T>(const Vector<2, U> &vector);

	T &operator [] (const size_t i)
	{
		assert(i < 2);
		
		return i <= 0 ? x : y;
	}

	const T &operator [] (const size_t i) const 
	{
		assert(i < 2);
		
		return i <= 0 ? x : y;
	}
};

template <typename T>
struct Vector<3, T>
{
	T x, y, z;

	Vector() : x(T()), y(T()), z(T())
	{

	}

	Vector(T x, T y, T z) : x(x), y(y), z(z)
	{

	}

	template <class U>
	Vector<3, T>(const Vector<3, U> &vector);

	T &operator [] (const size_t i)
	{
		assert(i < 3);
		
		return i <= 0 ? x : (1 == i ? y : z);
	}

	const T &operator [] (const size_t i) const
	{
		assert(i < 3);
		
		return i <= 0 ? x : (1 == i ? y : z);
	}

	float norm()
	{
		return sqrt(x * x + y * y + z * z);
	}

	Vector<3, T> &normalize(T l = 1)
	{
		*this = (*this)*(l / norm());
		
		return *this;
	}
};



template<size_t Dim, typename T>
T operator * (const Vector<Dim, T> &left, const Vector<Dim, T> &right)
{
	T result = T();

	for (size_t i = Dim; i--; result += left[i] * right[i]);
	
	return result;
}

template<size_t Dim, typename T>
Vector<Dim, T> operator + (Vector<Dim, T> &left, const Vector<Dim, T> &right)
{
	for (size_t i = Dim; i--; left[i] += right[i]);

	return left;
}

template<size_t Dim, typename T>
Vector<Dim, T> operator - (Vector<Dim, T> &left, const Vector<Dim, T> &right)
{
	for (size_t i = Dim; i--; left[i] -= right[i]);

	return left;
}

template<size_t Dim, typename T, typename U>
Vector<Dim, T> operator * (Vector<Dim, T> &left, const U &right)
{
	for (size_t i = Dim; i--; left[i] *= right);

	return left;
}

template<size_t Dim, typename T, typename U>
Vector<Dim, T> operator / (Vector<Dim, T> &left, const U &right)
{
	for (size_t i = Dim; i--; left[i] /= right);

	return left;
}

template<size_t Len, size_t Dim, typename T>
Vector<Len, T> embed(const Vector<Dim, T> &v, T fill = 1)
{
	Vector<Len, T> result;

	for (size_t i = Len; i--; result[i] = (i < Dim ? v[i] : fill));

	return result;
}

template<size_t Len, size_t Dim, typename T>
Vector<Len, T> proj(const Vector<Dim, T> &vector)
{
	Vector<Len, T> result;

	for (size_t i = Len; i--; result[i] = vector[i]);

	return result;
}

template <typename T>
Vector<3, T> cross(Vector<3, T> vector1, Vector<3, T> vector2)
{
	return Vector<3, T>(vector1.y * vector2.z - vector1.z * vector2.y, vector1.z * vector2.x - vector1.x * vector2.z, vector1.x * vector2.y - vector1.y * vector2.x);
}

template <size_t Dim, typename T>
ostream &operator << (ostream &os, Vector<Dim, T> &vector)
{
	for (unsigned int i = 0; i < Dim; ++i)
	{
		os << vector[i] << " ";
	}
	return os;
}



template<size_t Dim, typename T>
struct dt
{
	static T determine(const Matrix<Dim, Dim, T> &src)
	{
		T result = 0;

		for (size_t i = Dim; i--; result += src[0][i] * src.cofactor(0, i));

		return result;
	}
};

template<typename T>
struct dt<1, T>
{
	static T determine(const Matrix<1, 1, T> &src)
	{
		return src[0][0];
	}
};



template<size_t DimRows, size_t DimCols, typename T>
class Matrix
{
	Vector<DimCols, T> rows[DimRows];

public:
	Matrix() {}

	Vector<DimCols, T> &operator [] (const size_t i)
	{
		assert(i < DimRows);

		return rows[i];
	}

	const Vector<DimCols, T> &operator [] (const size_t i) const
	{
		assert(i < DimRows);

		return rows[i];
	}

	Vector<DimRows, T> col(const size_t i) const
	{
		assert(i < DimCols);

		Vector<DimRows, T> result;
		
		for (size_t j = DimRows; j--; result[j] = rows[j][i]);
		
		return result;
	}

	void setCol(size_t i, Vector<DimRows, T> vector)
	{
		assert(i < DimCols);

		for (size_t j = DimRows; j--; rows[j][i] = vector[j]);
	}

	static Matrix<DimRows, DimCols, T> identity()
	{
		Matrix<DimRows, DimCols, T> result;

		for (size_t i = DimRows; i--;)
		{
			for (size_t j = DimCols; j--; result[i][j] = (i == j));
		}
		
		return result;
	}

	T determine() const
	{
		return dt<DimCols, T>::determine(*this);
	}

	Matrix<DimRows - 1, DimCols - 1, T> getMinor(size_t row, size_t col) const
	{
		Matrix<DimRows - 1, DimCols - 1, T> result;

		for (size_t i = DimRows - 1; i--; )
		{
			for (size_t j = DimCols - 1; j--; result[i][j] = rows[i < row ? i : i + 1][j < col ? j : j + 1]);
		}

		return result;
	}

	T cofactor(size_t row, size_t col) const
	{
		return getMinor(row, col).determine()*((row + col) % 2 ? -1 : 1);
	}

	Matrix<DimRows, DimCols, T> adjugate() const
	{
		Matrix<DimRows, DimCols, T> result;

		for (size_t i = DimRows; i--; )
		{
			for (size_t j = DimCols; j--; result[i][j] = cofactor(i, j));
		}

		return result;
	}

	Matrix<DimRows, DimCols, T> invertTranspose()
	{
		Matrix<DimRows, DimCols, T> result = adjugate();

		T temp = result[0] * rows[0];

		return result / temp;
	}
};



template<size_t DimRows, size_t DimCols, typename T>
Vector<DimRows, T> operator * (const Matrix<DimRows, DimCols, T> &left, const Vector<DimCols, T> &right)
{
	Vector<DimRows, T> result;

	for (size_t i = DimRows; i--; result[i] = left[i] * right);

	return result;
}

template<size_t DimRows1, size_t DimCols1, size_t DimCols2, typename T>
Matrix<DimRows1, DimCols2, T> operator * (const Matrix<DimRows1, DimCols1, T> &left, const Matrix<DimCols1, DimCols2, T> &right)
{
	Matrix<DimRows1, DimCols2, T> result;

	for (size_t i = DimRows1; i--; )
	{
		for (size_t j = DimCols2; j--; result[i][j] = left[i] * right.col(j));
	}

	return result;
}

template<size_t DimRows, size_t DimCols, typename T>
Matrix<DimCols, DimRows, T> operator / (Matrix<DimRows, DimCols, T> left, const T &right)
{
	for (size_t i = DimRows; i--; left[i] = left[i] / right);

	return left;
}

template <size_t DimRows, size_t DimCols, typename T>
ostream &operator << (ostream& os, Matrix<DimRows, DimCols, T> &matrix)
{
	for (size_t i = 0; i < DimRows; ++i)
	{
		os << matrix[i] << '\n';
	}

	return os;
}



typedef Vector<2, float> Vector2float;
typedef Vector<2, int>   Vector2int;
typedef Vector<3, float> Vector3float;
typedef Vector<3, int>   Vector3int;
typedef Vector<4, float> Vector4float;
typedef Matrix<4, 4, float> Matrix4float;

//Matrix viewport(int x, int y, int width, int height, int depth);
//
//Matrix lookat(Vector3float eye, Vector3float center, Vector3float up);