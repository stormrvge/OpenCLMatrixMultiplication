#include "kernelExecutor.h"
#include <string>
#include <iostream>


int main()
{
	std::string kernel1 = "NaiveMethod.cl";
	std::string kernel2 = "TileMethod.cl";
	std::string kernel3 = "NaiveTransposedMethod.cl";

	KernelExecutor kernel_executor;

	kernel_executor.execute(kernel3, 3, 3, 1, true);

	//kernel_executor.execute(kernel3, 128, 128, 32);
	//kernel_executor.execute(kernel3, 256, 256, 32);
	//kernel_executor.execute(kernel3, 512, 512, 32);
	////kernel_executor.execute(kernel3, 1024, 1024, 32);

	//kernel_executor.execute(kernel1, 128, 128, 32);
	//kernel_executor.execute(kernel1, 256, 256, 32);
	//kernel_executor.execute(kernel1, 512, 512, 32);
	////kernel_executor.execute(kernel1, 1024, 1024, 32);

	

	// kernel_executor.execute(kernel1, 2048, 2048, 32);
	// kernel_executor.execute(kernel1, 4096, 4096, 32);

	//kernel_executor.execute(kernel2, 128, 128, 32);
	//kernel_executor.execute(kernel2, 256, 256, 32);
	//kernel_executor.execute(kernel2, 512, 512, 32);
	//kernel_executor.execute(kernel2, 1024, 1024, 32);
	// kernel_executor.execute(kernel2, 2048, 2048, 32);
	// kernel_executor.execute(kernel2, 4096, 4096, 32); 


	// TESTS FROM FILE
	//std::cout << "TESTS FROM FILE" << std::endl;
	//kernel_executor.execute(kernel1, "D:\\t256.txt", 32);
	//kernel_executor.execute(kernel1, "D:\\t512.txt", 32);
	//kernel_executor.execute(kernel1, "D:\\t1024.txt", 32);
	//kernel_executor.execute(kernel1, "D:\\t2048.txt", 32);

	//kernel_executor.execute(kernel2, "D:\\t256.txt", 32);
	//kernel_executor.execute(kernel2, "D:\\t512.txt", 32);
	//kernel_executor.execute(kernel2, "D:\\t1024.txt", 32);
	//kernel_executor.execute(kernel2, "D:\\t2048.txt", 32);


	return 0;
}