#include "matrix.h"

void Matrix::fillRandMatrix()
{
    float* matrix = (float*)malloc(sizeof(float) * this->matrix_size);

    for (int i = 0; i < this->row_size; i++)
    {
        for (int j = 0; j < this->col_size; j++)
        {
            matrix[j + i * this->row_size] = rand() % 10;
        }
    }

    for (int i = 0; i < this->row_size; i++)
    {
        for (int j = 0; j < this->col_size; j++)
        {
            this->data.push_back(matrix[j + i * this->row_size]);
        }
    }

    free(matrix);
}

Matrix Matrix::multiplicate(Matrix matrix1, Matrix matrix2)
{
    int m1_cols = matrix1.getColSize();
    int m2_cols = matrix2.getColSize();
    int m1_rows = matrix1.getRowSize();
    int m2_rows = matrix2.getRowSize();

    Matrix new_matrix(m1_cols, m2_rows);
    int new_col = new_matrix.getColSize();
    int new_row = new_matrix.getRowSize();

    float* matrix_data = new float[m1_cols * m2_rows];

    for (int i = 0; i < m1_rows; ++i)
    {
        for (int j = 0; j < matrix2.getColSize(); ++j)
        {
            float sum = 0.0f;
            for (int k = 0; k < m1_cols; ++k)
            {
                sum += matrix1.data.at(i + k * m1_cols) * matrix2.data.at(k + j * m2_cols);
            }
            matrix_data[i * m1_cols + j] = sum;
        }    
    } 

    for (int i = 0; i < m1_cols; i++)
    {
        for (int j = 0; j < m2_rows; j++)
        {
            new_matrix.data.push_back(matrix_data[i + j * m1_rows]);
        }
    }

    delete[] matrix_data;

    return new_matrix;
}


void Matrix::printMatrix() const
{
    for (int i = 0; i < this->row_size; i++)
    {
        for (int j = 0; j < this->col_size; j++)
        {
            printf("%0.1f ", this->data.at(i * row_size + j));
        }
        printf("\n");
    }
}

bool Matrix::dataEquals(const Matrix matrix) const
{
    if (this->matrix_size != matrix.getMatrixSize())
        return false;

    int cols = this->getColSize();
    int rows = this->getRowSize();

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if (!compare_float(matrix.data.at(i * cols + j), this->data.at(i * cols + j)))
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::compare_float(float x, float y, float epsilon) const {
    return (fabs(fabs(x) - fabs(y)) < epsilon) ? true : false;
}



int Matrix::getMatrixSize() const
{
    return this->matrix_size;
}

int Matrix::getRowSize() const
{
    return this->row_size;
}

int Matrix::getColSize() const
{
    return this->col_size;
}

std::vector<float> Matrix::getVector()
{
    return this->data;
}