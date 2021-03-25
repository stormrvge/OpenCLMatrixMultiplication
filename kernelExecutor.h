#ifndef MATRIX_MULTIPLICATION_KERNEL_EXECUTOR
#define MATRIX_MULTIPLICATION_KERNEL_EXECUTOR

#include <string>
#include "matrix.h"

class KernelExecutor
{
public:
	int matrixMultiplicate(std::string kernel_filepath, std::string matrix_filepath, int workgroup_size);
	int matrixMultiplicate(std::vector<Matrix> *matrixes, std::string kernel_filepath, int workgroup_size);
	int matrixTranspose(Matrix* input_matrix, std::string kernel_filepath, int workgroup_size);

private:
	int matrixMultiplicate(std::string kernel_filepath, std::vector<Matrix> *matrixes, int workgroup_size, double &exec_time);
};

#endif // !MATRIX_MULTIPLICATION_KERNEL_EXECUTOR
