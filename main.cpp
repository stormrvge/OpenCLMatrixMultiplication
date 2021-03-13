#include "kernelExecutor.h"
#include <string>


int main()
{
	std::string kernel1 = "NaiveMethod.cl";
	std::string kernel2 = "TileMethod.cl";

	KernelExecutor kernel_executor;
	// kernel_executor.execute(kernel1, "D:\\test1.txt", 1);	// 10x10
	// kernel_executor.execute(kernel1, "D:\\test2.txt", 25);	// 500x500
	// kernel_executor.execute(kernel1, "D:\\test3.txt", 32);  // 512x512
	// kernel_executor.execute(kernel1, "D:\\test4.txt", 20);  // 2000x2000
	// kernel_executor.execute(kernel1, "D:\\test6.txt", 1);  // 2000x2000

	// kernel_executor.execute(kernel2, "D:\\test6.txt", 1);
	// kernel_executor.execute(kernel2, "D:\\test3.txt", 32);

	kernel_executor.execute(kernel1, 128, 128, 32);
	kernel_executor.execute(kernel1, 256, 256, 32);
	kernel_executor.execute(kernel1, 512, 512, 32);
	kernel_executor.execute(kernel1, 1024, 1024, 32);
	kernel_executor.execute(kernel1, 2048, 2048, 32);
	kernel_executor.execute(kernel1, 4096, 4096, 32);

	kernel_executor.execute(kernel2, 128, 128, 32);
	kernel_executor.execute(kernel2, 256, 256, 32);
	kernel_executor.execute(kernel2, 512, 512, 32);
	kernel_executor.execute(kernel2, 1024, 1024, 32);
	kernel_executor.execute(kernel2, 2048, 2048, 32);
	kernel_executor.execute(kernel2, 4096, 4096, 32); 

	return 0;
}