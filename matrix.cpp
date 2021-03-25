#include "matrix.h"

Matrix::Matrix(int col_size, int row_size) : col_size(col_size), 
        row_size(row_size), matrix_size(row_size * col_size), data(matrix_size, 0) {}

void Matrix::fillRandMatrix()
{
    for (int i = 0; i < this->row_size; i++)
    {
        for (int j = 0; j < this->col_size; j++)
        {
            data[i + j * row_size] = rand() % 10;
        }
    }
}

Matrix Matrix::multiplicate(const Matrix &matrix1, const Matrix &matrix2)
{
    int m1_cols = matrix1.getColSize();
    int m2_cols = matrix2.getColSize();
    int m1_rows = matrix1.getRowSize();
    int m2_rows = matrix2.getRowSize();

    Matrix new_matrix(m1_cols, m2_rows);
    int new_col = new_matrix.getColSize();
    int new_row = new_matrix.getRowSize();

    for (int i = 0; i < m1_rows; ++i)
    {
        for (int j = 0; j < matrix2.getColSize(); ++j)
        {
            float sum = 0.0f;
            for (int k = 0; k < m1_cols; ++k)
            {
                sum += matrix1.data[i + k * m1_cols] * matrix2.data[k + j * m2_cols];
            }
            new_matrix.data[i + j * m1_cols] = sum;
        }    
    } 

    return new_matrix;
}


void Matrix::printMatrix() const
{
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < col_size; j++)
        {
            printf("%0.1f ", data[i * row_size + j]);
        }
        printf("\n");
    }
}

bool Matrix::dataEquals(const Matrix matrix) const
{
    if (matrix_size != matrix.getMatrixSize())
        return false;

    int cols = getColSize();
    int rows = getRowSize();

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (!compare_float(matrix.data[i * cols + j], data[i * cols + j]))
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::compare_float(float x, float y, float epsilon) const {
    return std::abs(x - y) <= std::max(std::abs(x), std::abs(y)) * std::numeric_limits<float>::epsilon();
}



int Matrix::getMatrixSize() const
{
    return matrix_size;
}

int Matrix::getRowSize() const
{
    return row_size;
}

int Matrix::getColSize() const
{
    return col_size;
}

float* Matrix::getData()
{
    return data.data();
}