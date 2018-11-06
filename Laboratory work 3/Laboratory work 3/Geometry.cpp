#include "Geometry.h"


template<>
template<>
Vector3<int>::Vector3(const Vector3<float> &vector) : x(int(vector.x + 0.5f)), y(int(vector.y + 0.5f)), z(int(vector.z + 0.5f))
{

}

template<>
template<>
Vector3<float>::Vector3(const Vector3<int> &vector) : x(float(vector.x)), y(float(vector.y)), z(float(vector.z))
{

}


Matrix::Matrix(int r, int c) : matrix(vector<vector<float> >(r, vector<float>(c, 0.f))), rows(r), cols(c)
{

}

int Matrix::getNumberOfRow()
{
	return rows;
}

int Matrix::getNumberOfCol()
{
	return cols;
}

Matrix Matrix::identity(int dimensions)
{
	Matrix E(dimensions, dimensions);

	for (int i = 0; i < dimensions; ++i)
	{
		for (int j = 0; j < dimensions; ++j)
		{
			E[i][j] = (i == j ? 1.f : 0.f);
		}
	}

	return E;
}

vector<float> &Matrix::operator [] (const int i)
{
	assert(i >= 0 && i < rows);

	return matrix[i];
}

Matrix Matrix::operator * (const Matrix &right)
{
	assert(cols == right.rows);

	Matrix result(rows, right.cols);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < right.cols; ++j)
		{
			result.matrix[i][j] = 0.f;
			for (int k = 0; k < cols; k++)
			{
				result.matrix[i][j] += matrix[i][k] * right.matrix[k][j];
			}
		}
	}

	return result;
}

Matrix Matrix::transpose()
{
	Matrix result(cols, rows);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			result[j][i] = matrix[i][j];
		}
	}

	return result;
}

Matrix Matrix::inverse()
{
	assert(rows == cols);

	//Augmenting the square matrix with the identity matrix of the same dimensions a => [ai]

	Matrix result(rows, cols * 2);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++i)
		{
			result[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < rows; ++i)
	{
		result[i][i + cols] = 1;
	}

	//First pass
	for (int i = 0; i < rows - 1; ++i)
	{
		//Normalize the first row
		for (int j = result.cols - 1; j >= 0; --j)
		{
			result[i][j] /= result[i][i];
		}

		for (int j = i + 1; j < rows; ++j)
		{
			float coefficient = result[j][i];
			for (int k = 0; k < result.cols; ++k)
			{
				result[j][k] -= result[i][k] * coefficient;
			}
		}
	}

	//Normalize the last row
	for (int j = result.cols - 1; j >= rows - 1; --j)
	{
		result[rows - 1][j] /= result[rows - 1][rows - 1];
	}

	//Second pass
	for (int i = rows - 1; i > 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			float coefficient = result[j][i];
			for (int k = 0; k < result.cols; ++k)
			{
				result[j][k] -= result[i][k] * coefficient;
			}
		}
	}

	//Cut the identity matrix back
	Matrix truncate(rows, cols);

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			truncate[i][j] = result[i][j + cols];
		}
	}

	return truncate;
}

ostream &operator << (ostream &os, Matrix &m)
{
	for (int i = 0; i < m.getNumberOfRow(); ++i)
	{
		for (int j = 0; j < m.getNumberOfCol(); ++j)
		{
			os << m[i][j];
			if (j < m.getNumberOfCol() - 1)
			{
				os << "\t";
			}
		}
		os << "\n";
	}
	return os;
}