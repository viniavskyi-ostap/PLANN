#ifndef PLANN_MATRIX_H
#define PLANN_MATRIX_H

#include <vector>

class Matrix {
    int rows_number;
    int columns_number;

    float* data;

    Matrix(int rows_number, int columns_number);
    ~Matrix();


    int get_rows_number();
    int get_columns_number();

    float get(int row, int column);
    void set(int row, int colunn, float value);

    void multiply(Matrix &rhs, Matrix &result);
    void transpose(Matrix &result);
    void map(float(*f)(float), Matrix& result);
    void combine(Matrix& rhs, float(*f)(float, float), Matrix& result);
    void reduce_row(float(*f)(float, float));
    void add_column(Matrix& rhs);
    void rows_submatrix(Matrix& result, std::vector<int> indexes, int start, int end);
};

#endif
