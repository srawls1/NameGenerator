#include "stdafx.h"
#include "Matrix.h"


Matrix::Matrix(int rows, int columns)
{
	r = rows;
	c = columns;

	int count = rows * columns;
	data = new float[count];
	for (int i = 0; i < count; ++i)
	{
		data[i] = 0.f;
	}
}

Matrix::Matrix(Matrix& copy)
{
	r = copy.r;
	c = copy.c;

	int count = r * c;
	data = new float[count];
	for (int i = 0; i < count; ++i)
	{
		data[i] = copy.data[i];
	}
}

Matrix::Matrix(Matrix&& toMove)
{
	r = toMove.r;
	c = toMove.c;

	toMove.c = 0;
	toMove.r = 0;

	data = toMove.data;
	toMove.data = nullptr;
}

Matrix::~Matrix()
{
	delete[] data;
}


Matrix& Matrix::operator=(Matrix& copy)
{
	delete[] data;

	r = copy.r;
	c = copy.c;

	int count = r * c;
	data = new float[count];
	for (int i = 0; i < count; ++i)
	{
		data[i] = copy.data[i];
	}
}

float Matrix::getAt(int row, int column)
{
	return data[row * c + column];
}

void Matrix::setAt(int row, int column, float value)
{
	data[row * c + column] = value;
}

Matrix identity(int size)
{
	Matrix result(size, size);
	for (int i = 0; i < size; ++i)
	{
		result.setAt(i, i, 1.f);
	}
	return result;
}

Matrix operator*(Matrix& A, Matrix& B)
{
	Matrix result(A.numRows(), B.numColumns());

	for (int row = 0; row < A.numRows(); ++row)
	{
		for (int column = 0; column < B.numColumns(); ++column)
		{
			float cellResult = 0.f;
			for (int x = 0; x < A.numColumns() && x < B.numRows; ++x)
			{
				cellResult += A.getAt(row, x) * B.getAt(x, column);
			}
			result.setAt(row, column, cellResult);
		}
	}

	return result;
}