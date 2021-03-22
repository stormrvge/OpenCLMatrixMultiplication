#ifndef MATRIX_MULTIPLICATION_KERNEL_EXECUTOR
#define MATRIX_MULTIPLICATION_KERNEL_EXECUTOR

#include <string>
#include "matrix.h"

class KernelExecutor
{
public:
	int execute(std::string kernel_filepath, std::string matrix_filepath, int workgroup_size, bool transposed_method = false);
	int execute(std::string kernel_filepath, const int matrix_cols, const int matrix_rows, int workgroup_size, bool transposed_method = false);

private:
	int transposeMatrix(Matrix* input_matrix, std::string kernel_filepath, int workgroup_size);
};

#endif // !MATRIX_MULTIPLICATION_KERNEL_EXECUTOR
