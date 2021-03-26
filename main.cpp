#include <string>
#include <iostream>

#include "kernelExecutor.h"
#include "tester.h"

int main()
{
	Tester tester;
	std::vector<std::string> multiplication_kernels;
	multiplication_kernels.push_back("kernels/NaiveMethod.cl");
	multiplication_kernels.push_back("kernels/TileMethod.cl");

	std::vector<std::string> transpose_kernels;
	transpose_kernels.push_back("kernels/TransposeMatrix.cl");

	int start_colsize = 64;
	int start_rowsize = 64;
	int number_of_tests = 64;

	// tester.testMultiplicationKernels(multiplication_kernels, number_of_tests, start_colsize, start_rowsize);
	tester.testTranposingKernels(transpose_kernels, number_of_tests + 3, start_colsize, start_rowsize);

	return 0;
}