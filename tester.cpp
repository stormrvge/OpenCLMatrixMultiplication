#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>

#include "tester.h"
#include "kernelExecutor.h"

int Tester::test_number = 1;

std::vector<Matrix> Tester::readMatrixFromFile(const std::string& filepath)
{
    std::ifstream test(filepath);
    std::stringstream ss;

    if (!test.is_open())
    {
        "Unable to read file: " + filepath;
    }

    ss << test.rdbuf();

    int n, k, m;

    ss >> n >> k >> m;

    if (ss.fail())
    {
        "In file: " + filepath + "\nUnable to read values: n k m";
    }


    Matrix matrix1(n, k);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {       
            float num = 0.0f;
            ss >> num;

            matrix1.getData()[j + i * m] = num;

            if (ss.fail())
            {
                std::cout << "In file: " + filepath + "\nUnable to read value: a[" + std::to_string(i) + "][" + std::to_string(j) + "]" << std::endl;
            }
        }
    }

    Matrix matrix2(k, m);
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < m; j++)
        {
            float num = 0.0f;
            ss >> num;

            matrix2.getData()[j + i * m] = num;
            if (ss.fail())
            {
                std::cout << "In file: " + filepath + "\nUnable to read value: b[" + std::to_string(i) + "][" + std::to_string(j) + "]" << std::endl;
            }
        }
    }

    Matrix matrix3(n, m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            float num = 0.0f;
            ss >> num;

            matrix3.getData()[j + i * m] = num;
            if (ss.fail())
            {
                std::cout << "In file: " + filepath + "\nUnable to read value: c[" + std::to_string(i) + "][" + std::to_string(j) + "]" << std::endl;
            }
        }
    }

    std::vector<Matrix> vector;
    vector.push_back(matrix1);
    vector.push_back(matrix2);
    vector.push_back(matrix3);

    return vector;
}

void Tester::isAnswerCorrect(const Matrix matrix1, const Matrix matrix2, std::string kernel_name, const int error_code, const double exec_time) const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    if (matrix1.dataEquals(matrix2) && error_code == 0)
    {
        printf("TEST %d: %s --- MATRIX SIZE: %dx%d --- EXECUTION TIME: %0.5f ms --- TEST ", test_number++, kernel_name.c_str(),
            matrix1.getColSize(), matrix1.getColSize(), exec_time);
        // SetConsoleTextAttribute(hConsole, 10);
        std::cout << "<OK>" << std::endl;
        // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
    }
    else
    {
        printf("TEST %d: %s --- MATRIX SIZE: %dx%d --- EXECUTION TIME: %0.5f ms --- TEST ", test_number++, kernel_name.c_str(),
            matrix1.getColSize(), matrix1.getColSize(), exec_time);
        // SetConsoleTextAttribute(hConsole, 12);
        std::cout << "<FAILED>" << std::endl;
        // SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
        if (error_code != 0)
        {
            printf("TEST %d: ERROR_CODE: %d\n", test_number - 1, error_code);
        }
    }
}


int Tester::testMultiplicationKernels(std::vector<std::string> kernels, int num_of_test, int col_size, int row_size)
{
    KernelExecutor kernel_executor;
    std::vector<Matrix> matrixes;

    int start_col = col_size;
    int start_row = row_size;

    int error_code = 0;
    
    std::cout << "--- RUNTIME TESTS ---" << std::endl;
    for (int i = 0; i < kernels.size(); i++)
    {
        for (int j = 0; j < num_of_test; j++)
        {
            generateMatrixes(&matrixes, col_size, row_size);
            error_code = kernel_executor.matrixMultiplicate(&matrixes, kernels[i], 32);
            row_size += 32;
            col_size += 32;
        }

        row_size = start_row;
        col_size = start_col;

        if (error_code != 0)
        {
            printf("--- ERROR ---\n--- CODE OF ERROR: [%d] ---", error_code);
            break;
        }
    }

    // TESTS FROM FILE
    //std::cout << "TESTS FROM FILE" << std::endl;
    //kernel_executor.matrixMultiplicate(kernel1, "D:\\t256.txt", 32);
    //kernel_executor.matrixMultiplicate(kernel1, "D:\\t512.txt", 32);
    //kernel_executor.matrixMultiplicate(kernel1, "D:\\t1024.txt", 32);
    //kernel_executor.matrixMultiplicate(kernel1, "D:\\t2048.txt", 32);

    //kernel_executor.matrixMultiplicate(kernel2, "D:\\t256.txt", 32);
    //kernel_executor.matrixMultiplicate(kernel2, "D:\\t512.txt", 32);
    //kernel_executor.matrixMultiplicate(kernel2, "D:\\t1024.txt", 32);
    //kernel_executor.matrixMultiplicate(kernel2, "D:\\t2048.txt", 32);

    return error_code;
}

int Tester::testTranposingKernels(std::vector<std::string> kernels, int num_of_tests, int col_size, int row_size)
{
    KernelExecutor kernel_executor;
    int start_col = col_size;
    int start_row = row_size;
    int error_code = 0;

    std::cout << "--- RUNTIME TESTS ---" << std::endl;
    for (int i = 0; i < kernels.size(); i++)
    {
        for (int j = 0; j < num_of_tests; j++)
        {
            Matrix random_matrix(col_size, row_size);
            random_matrix.fillRandMatrix();
            error_code = kernel_executor.matrixTranspose(&random_matrix, kernels[i], 32);
            row_size += 32;
            col_size += 32;
        }

        row_size = start_row;
        col_size = start_col;

        if (error_code != 0)
        {
            printf("--- ERROR ---\n--- CODE OF ERROR: [%d] ---", error_code);
            break;
        }
    }

    return error_code;
}

void Tester::generateMatrixes(std::vector<Matrix>* matrixes, int cols_size, int row_size)
{
    matrixes->clear();

    for (int i = 0; i < 3; i++)
    {
        (*matrixes).push_back(Matrix(cols_size, row_size));
        (*matrixes)[i].fillRandMatrix();
    }
}