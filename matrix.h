#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <vector>

class Matrix
{
public:
	Matrix(int col_size, int row_size) : col_size(col_size), row_size(row_size), matrix_size(row_size * col_size) {}

	void fillRandMatrix();
	static Matrix multiplicate(const Matrix matrix1, const Matrix matrix);
	void printMatrix() const;
	int getMatrixSize() const;
	int getRowSize() const;
	int getColSize() const;
	std::vector<float> getVector();		// todo
	bool dataEquals(Matrix matrix) const;

	std::vector<float> data;		//todo
private:
	bool compare_float(float x, float y, float epsilon = 5.00f) const;

	int row_size;
	int col_size;
	int matrix_size;
};

#endif // !MATRIX_MULTIPLICATION_H
