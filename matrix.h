#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <vector>

class Matrix
{
public:
	Matrix(int col_size, int row_size);

	static Matrix multiplicate(const Matrix matrix1, const Matrix matrix);
	void fillRandMatrix();
	void matrixDataCopy(const Matrix input_matrix);
	void printMatrix() const;
	int getMatrixSize() const;
	int getRowSize() const;
	int getColSize() const;
	double* getData();
	bool dataEquals(Matrix matrix) const;

private:
	bool compare_float(double x, double y, double epsilon = 5.00f) const;

	int row_size;
	int col_size;
	int matrix_size;
	std::vector<double> data;	
};

#endif // !MATRIX_MULTIPLICATION_H
