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


int KernelExecutor::matrixMultiplicate(std::string kernel_filepath, std::string matrix_filepath, int workgroup_size) 
{
    Tester tester;
    int error_code = 0;
    double exec_time = 0;

    std::vector<Matrix> tested_matrixes = tester.readMatrixFromFile(matrix_filepath);

    Matrix matrix1 = tested_matrixes[0];
    Matrix matrix2 = tested_matrixes[1];
    Matrix matrix3 = tested_matrixes[2];

    error_code = matrixMultiplicate(kernel_filepath, tested_matrixes[0], tested_matrixes[1], tested_matrixes[2], exec_time);
    tester.isMultiplicationCorrect(tested_matrixes[2], matrix3, kernel_filepath, error_code, exec_time);

    return error_code;
}


int KernelExecutor::matrixMultiplicate(Matrix &matrix1, Matrix &matrix2, Matrix &output_matrix, std::string kernel_filepath, double &exec_time) {
    int error_code = 0;

    Matrix valid_matrix = Matrix::multiplicate(matrix1, matrix2);

    error_code = matrixMultiplicate(kernel_filepath, matrix1, matrix2, output_matrix, exec_time);

    return error_code;
}


int KernelExecutor::matrixMultiplicate(std::string kernel_filepath, Matrix &matrix1, Matrix &matrix2, Matrix &output_matrix, double &exec_time)
{
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
    cl::Buffer matrixA(context, CL_MEM_READ_ONLY, matrix1.getMatrixSize() * sizeof(float));
    cl::Buffer matrixB(context, CL_MEM_READ_ONLY, matrix2.getMatrixSize() * sizeof(float));
    cl::Buffer matrixC(context, CL_MEM_READ_WRITE, output_matrix.getMatrixSize() * sizeof(float));

    error_code = command_queue.enqueueWriteBuffer(matrixA, CL_TRUE, 0, matrix1.getMatrixSize() * sizeof(float), matrix1.getData());
    error_code = command_queue.enqueueWriteBuffer(matrixB, CL_TRUE, 0, matrix2.getMatrixSize() * sizeof(float), matrix2.getData());

    // Create a program from the kernel source
    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
    cl::Program program(context, source, &error_code);

    // Build the program
    program.build();

    // Create the OpenCL kernel
    cl::Kernel kernel(program, "vector_add");

    const int M = matrix1.getRowSize();
    const int N = matrix2.getRowSize();
    const int K = output_matrix.getRowSize();

    // Set the arguments of the kernel
    error_code = kernel.setArg(0, matrixA);
    error_code = kernel.setArg(1, matrixB);
    error_code = kernel.setArg(2, matrixC);
    error_code = kernel.setArg(3, M);
    error_code = kernel.setArg(4, N);
    error_code = kernel.setArg(5, K);


    // Execute the OpenCL kernel on the list
    const int TS = 32;
    const size_t local[2] = { TS, TS };
    const size_t global[2] = { matrix1.getRowSize(), matrix1.getRowSize() };


    error_code = command_queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global[0], global[1]), cl::NDRange(local[0], local[1]), NULL, &event);
    error_code = command_queue.finish();
    error_code = command_queue.enqueueReadBuffer(matrixC, CL_TRUE, 0, output_matrix.getMatrixSize() * sizeof(float), output_matrix.getData());


    cl_ulong time_start;
    cl_ulong time_end;

    event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);

    exec_time = (time_end - time_start) / 1000000.0;


    return error_code;
}

int KernelExecutor::matrixTranspose(Matrix &input_matrix, std::string kernel_filepath, double &exec_time)
{
    Matrix output_matrix(input_matrix.getColSize(), input_matrix.getRowSize());

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
    cl::Buffer in_matrix(context, CL_MEM_READ_ONLY, input_matrix.getMatrixSize() * sizeof(float));
    cl::Buffer out_matrix(context, CL_MEM_READ_WRITE, input_matrix.getMatrixSize() * sizeof(float));

    error_code = command_queue.enqueueWriteBuffer(in_matrix, CL_TRUE, 0, input_matrix.getMatrixSize() * sizeof(float), input_matrix.getData());

    // Create a program from the kernel source
    cl::Program::Sources source(1, std::make_pair(sourceCode.c_str(), sourceCode.length() + 1));
    cl::Program program(context, source, &error_code);

    // Build the program
    program.build();

    // Create the OpenCL kernel
    cl::Kernel kernel(program, "transpose");

    const int COLS = input_matrix.getColSize();
    const int ROWS = input_matrix.getRowSize();
    

    // Set the arguments of the kernel
    error_code = kernel.setArg(0, in_matrix);
    error_code = kernel.setArg(1, out_matrix);
    error_code = kernel.setArg(2, ROWS);
    error_code = kernel.setArg(3, COLS);


    // Execute the OpenCL kernel on the list
    const int TS = 32;
    const size_t local[2] = { TS, TS };
    const size_t global[2] = { COLS, ROWS };

    error_code = command_queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(global[0], global[1]), cl::NDRange(local[0], local[1]), NULL, &event);
    error_code = command_queue.finish();
    error_code = command_queue.enqueueReadBuffer(out_matrix, CL_TRUE, 0, input_matrix.getMatrixSize() * sizeof(float), output_matrix.getData());

    cl_ulong time_start;
    cl_ulong time_end;

    event.getProfilingInfo(CL_PROFILING_COMMAND_START, &time_start);
    event.getProfilingInfo(CL_PROFILING_COMMAND_END, &time_end);

    exec_time = (time_end - time_start) / 1000000.0;
    input_matrix = output_matrix;

    return error_code;
}