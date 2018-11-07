#include "Geometry.h"


template<>
template<>
Vector<3, int>::Vector(const Vector<3, float> &vector) : x(int(vector.x + 0.5f)), y(int(vector.y + 0.5f)), z(int(vector.z + 0.5f)) {}

template<>
template<>
Vector<3, float>::Vector(const Vector<3, int> &vector) : x(float(vector.x)), y(float(vector.y)), z(float(vector.z)) {}

template<>
template<>
Vector<2, int>::Vector(const Vector<2, float> &vector) : x(int(vector.x + 0.5f)), y(int(vector.y + 0.5f)) {}

template<>
template<>
Vector<2, float>::Vector(const Vector<2, int> &vector) : x(float(vector.x)), y(float(vector.y)) {}


//Matrix viewport(int x, int y, int width, int height, int depth)
//{
//	Matrix matrix = Matrix::identity(4);
//
//	matrix[0][3] = x + width * 0.5f;
//	matrix[1][3] = y + width * 0.5f;
//	matrix[2][3] = depth * 0.5f;
//
//	matrix[0][0] = width * 0.5f;
//	matrix[1][1] = width * 0.5f;
//	matrix[2][2] = depth * 0.5f;
//
//	return matrix;
//}
//
//Matrix lookat(Vector3float eye, Vector3float center, Vector3float up)
//{
//	Vector3float z = (eye - center).normalize();
//	Vector3float x = (up^z).normalize();
//	Vector3float y = (z^x).normalize();
//
//	Matrix Minv = Matrix::identity(4);
//	Matrix Tr = Matrix::identity(4);
//
//	for (int i = 0; i < 3; i++)
//	{
//		Minv[0][i] = x[i];
//		Minv[1][i] = y[i];
//		Minv[2][i] = z[i];
//
//		Tr[i][3] = -center[i];
//	}
//
//	return Minv * Tr;
//}