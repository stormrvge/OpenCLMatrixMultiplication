#include <stdio.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "kernelExecutor.h"
#include "matrix.h"
#include "tester.h"


#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#include <CL/cl.hpp>
#endif

#define MAX_SOURCE_SIZE (0x100000)


int KernelExecutor::execute(std::string kernel_filepath, std::string matrix_filepath, int workgroup_size) {
    Tester tester;
    std::vector<Matrix> tested_matrixes = tester.readMatrixFromFile(matrix_filepath);

    Matrix matrix1 = tested_matrixes[0];
    Matrix matrix2 = tested_matrixes[1];
    Matrix matrix3 = tested_matrixes[2];
    

    // Load the kernel source code into the array source_str
    std::ifstream sourceFile(kernel_filepath);
    std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

    int error_code = 0;

    // Get platform and device information
    std::vector<cl::Platform> platforms;
    error_code = cl::Platform::get(&platforms);
    cl::Platform platform = platforms[0];

    std::vector<cl::Device> devices;
    error_code = platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


    // CL Time
    cl::Event event;

    // Create an OpenCL context
    // cl::Context context(NULL, 1, &device_id, NULL, NULL, &ret);
    cl::Context context(devices[0]);

    // Create a command queue
    cl::CommandQueue command_queue(context, devices[0], CL_QUEUE_PROFILING_ENABLE, &error_code);

    // Create memory buffers on the device for each vector 
    cl::Buffer matrixA(context, CL_MEM_READ_ONLY, matrix1.getVector().size() * sizeof(float));
    cl::Buffer matrixB(context, CL_MEM_READ_ONLY, matrix2.getVector().size() * sizeof(float));
    cl::Buffer matrixC(context, CL_MEM_READ_WRITE, matrix3.getVector().size() * sizeof(float));

    error_code = command_queue.enqueueWriteBuffer(matrixA, CL_TRUE, 0, matrix1.getVector().size() * sizeof(float), matrix1.data.data());
    error_code = command_queue.enqueueWriteBuffer(matrixB, CL_TRUE, 0, matrix2.getVector().size() * sizeof(float), matrix2.data.data());

    // Create a program from the kernel source
    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
    cl::Program program(context, source, &error_code);

    // Build the program
    program.build();

    // Create the OpenCL kernel
    cl::Kernel kernel(program, "vector_add");

    const int M = matrix1.getRowSize();
    const int N = matrix1.getRowSize();
    const int K = matrix1.getRowSize();

    // Set the arguments of the kernel
    error_code = kernel.setArg(0, matrixA);
    error_code = kernel.setArg(1, matrixB);
    error_code = kernel.setArg(2, matrixC);
    error_code = kernel.setArg(3, M);
    error_code = kernel.setArg(4, N);
    error_code = kernel.setArg(5, K);


    // Execute the OpenCL kernel on the list
    const int TS = workgroup_size;
    const size_t local[2] = { TS, TS };
    const size_t global[2] = { matrix1.getRowSize(), matrix1.getRowSize() };


    error_code = command_queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global[0], global[1]), cl::NDRange(local[0], local[1]), NULL, &event);
    error_code = command_queue.finish();
    error_code = command_queue.enqueueReadBuffer(matrixC, CL_TRUE, 0, matrix3.getVector().size() * sizeof(float), matrix3.data.data());
    

    cl_ulong time_start;
    cl_ulong time_end;

    event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);

    double exec_time = (time_end - time_start) / 1000000.0;


    tester.isAnswerCorrect(tested_matrixes[2], matrix3, kernel_filepath, error_code, exec_time);
   

    return error_code;
}


int KernelExecutor::execute(std::string kernel_filepath, const int matrix_cols, const int matrix_rows, int workgroup_size) {
    Tester tester;

    Matrix matrix1(matrix_cols, matrix_rows);
    Matrix matrix2(matrix_cols, matrix_rows);
    Matrix matrix3(matrix_cols, matrix_rows);

    matrix1.fillRandMatrix();
    matrix2.fillRandMatrix();
    matrix3.fillRandMatrix();


    // Load the kernel source code into the array source_str
    std::ifstream sourceFile(kernel_filepath);
    std::string sourceCode(std::istreambuf_iterator<char>(sourceFile), (std::istreambuf_iterator<char>()));

    int error_code = 0;

    // Get platform and device information
    std::vector<cl::Platform> platforms;
    error_code = cl::Platform::get(&platforms);
    cl::Platform platform = platforms[0];

    std::vector<cl::Device> devices;
    error_code = platform.getDevices(CL_DEVICE_TYPE_GPU, &devices);


    // CL Time
    cl::Event event;

    // Create an OpenCL context
    // cl::Context context(NULL, 1, &device_id, NULL, NULL, &ret);
    cl::Context context(devices[0]);

    // Create a command queue
    cl::CommandQueue command_queue(context, devices[0], CL_QUEUE_PROFILING_ENABLE, &error_code);

    // Create memory buffers on the device for each vector 
    cl::Buffer matrixA(context, CL_MEM_READ_ONLY, matrix1.getVector().size() * sizeof(float));
    cl::Buffer matrixB(context, CL_MEM_READ_ONLY, matrix2.getVector().size() * sizeof(float));
    cl::Buffer matrixC(context, CL_MEM_READ_WRITE, matrix3.getVector().size() * sizeof(float));

    error_code = command_queue.enqueueWriteBuffer(matrixA, CL_TRUE, 0, matrix1.getVector().size() * sizeof(float), matrix1.data.data());
    error_code = command_queue.enqueueWriteBuffer(matrixB, CL_TRUE, 0, matrix2.getVector().size() * sizeof(float), matrix2.data.data());

    // Create a program from the kernel source
    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
    cl::Program program(context, source, &error_code);

    // Build the program
    program.build();

    // Create the OpenCL kernel
    cl::Kernel kernel(program, "vector_add");

    const int M = matrix1.getRowSize();
    const int N = matrix1.getRowSize();
    const int K = matrix1.getRowSize();

    // Set the arguments of the kernel
    error_code = kernel.setArg(0, matrixA);
    error_code = kernel.setArg(1, matrixB);
    error_code = kernel.setArg(2, matrixC);
    error_code = kernel.setArg(3, M);
    error_code = kernel.setArg(4, N);
    error_code = kernel.setArg(5, K);


    // Execute the OpenCL kernel on the list
    const int TS = workgroup_size;
    const size_t local[2] = { TS, TS };
    const size_t global[2] = { matrix1.getRowSize(), matrix1.getRowSize() };


    error_code = command_queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global[0], global[1]), cl::NDRange(local[0], local[1]), NULL, &event);
    error_code = command_queue.finish();
    error_code = command_queue.enqueueReadBuffer(matrixC, CL_TRUE, 0, matrix3.getVector().size() * sizeof(float), matrix3.data.data());


    cl_ulong time_start;
    cl_ulong time_end;

    event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);

    double exec_time = (time_end - time_start) / 1000000.0;



    // не хватило ума написать executor внутри тестера
    if (error_code == 0)
    {
        printf("TEST: %s --- MATRIX SIZE: %dx%d --- EXECUTION TIME: %0.5f ms ---\n", kernel_filepath.c_str(),
            matrix1.getColSize(), matrix1.getColSize(), exec_time);
    }


    return error_code;
}