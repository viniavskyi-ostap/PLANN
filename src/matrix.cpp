#include "matrix.h"


class Matrix {
    int rows_number;
    int columns_number;
    float* data;

    Matrix (int rows_number, int columns_number) {
        this->rows_number = rows_number;
        this->columns_number = columns_number;

        data = new float[rows_number * columns_number];
    }

    ~Matrix() {
        delete[] data;
    }

    void multiply(Matrix& rhs, Matrix& result) {
    }

};

