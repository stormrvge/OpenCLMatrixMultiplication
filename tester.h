#ifndef MATRIX_MULTIPLICATION_TESTER
#define MATRIX_MULTIPLICATION_TESTER

#include "matrix.h"
#include <string>

class Tester
{
public:
	std::vector<Matrix> readMatrixFromFile(const std::string& filepath);
	void isMultiplicationCorrect(const Matrix &matrix1, const Matrix &matrix2, std::string kernel_name, const int error_code, const double exec_time) const;
	void isTransposingCorrect(Matrix& input_matrix, Matrix& output_matrix, std::string kernel_name, const int error_code, const double exec_time) const;
	int testMultiplicationKernels(std::vector<std::string> kernels, int num_of_test, int col_size, int row_size);
	int testTranposingKernels(std::vector<std::string> kernels, int num_of_tests, int col_size, int row_size);

private:
	static int test_number;
	void generateMatrixes(std::vector<Matrix> &matrixes, int cols_size, int row_size);
	bool compare_float(float x, float y, float epsilon = 1.00f) const;
};

#endif // !MATRIX_MULTIPLICATION_TESTER
