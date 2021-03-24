#include "tester.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>

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