#ifndef MATRIX_MULTIPLICATION_TESTER
#define MATRIX_MULTIPLICATION_TESTER

#include "matrix.h"
#include <string>

class Tester
{
public:
	Tester();
	std::vector<Matrix> readMatrixFromFile(const std::string& filepath);
	void isAnswerCorrect(const Matrix matrix1, const Matrix matrix2, std::string kernel_name, const int error_code, const double exec_time) const;

private:
	static int test_number;
};

#endif // !MATRIX_MULTIPLICATION_TESTER
