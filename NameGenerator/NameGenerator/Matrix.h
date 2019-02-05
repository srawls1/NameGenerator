#pragma once
class Matrix
{
private:
	int r;
	int c;
	float* data;

public:
	Matrix(int rows, int columns);
	Matrix(Matrix& copy);
	Matrix(Matrix&& toMove);
	~Matrix();
	Matrix& operator=(Matrix& copy);

	int numRows() { return r; }
	int numColumns() { return c; }
	float getAt(int row, int column);
	void setAt(int row, int column, float value);
};

Matrix operator*(Matrix& A, Matrix& B);