#ifndef MATRIX_MULTIPLICATION_KERNEL_EXECUTOR
#define MATRIX_MULTIPLICATION_KERNEL_EXECUTOR

#include <string>
#include "matrix.h"

class KernelExecutor
{
public:
	int matrixMultiplicate(std::string kernel_filepath, std::string matrix_filepath, int workgroup_size);
	int matrixMultiplicate(Matrix &matrix1, Matrix &matrix2, Matrix &output_matrix, std::string kernel_filepath, double &exec_time);
	int matrixTranspose(Matrix &input_matrix, std::string kernel_filepath, double &exec_time);

private:
	int matrixMultiplicate(std::string kernel_filepath, Matrix &matrix1, Matrix &matrix2, Matrix &output_matrix, double& exec_time);
};

#endif // !MATRIX_MULTIPLICATION_KERNEL_EXECUTOR