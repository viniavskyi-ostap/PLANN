#include "matrix.h"



Matrix::Matrix (int rows_number, int columns_number) {
    this->rows_number = rows_number;
    this->columns_number = columns_number;

    data = new float[rows_number * columns_number];
}

Matrix::~Matrix() {
    delete[] data;
}

void Matrix::multiply(Matrix& rhs, Matrix& result) {

}


