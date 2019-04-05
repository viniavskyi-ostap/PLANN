#ifndef PLANN_MATRIX_H
#define PLANN_MATRIX_H

#include <vector>
#include <string>

class Matrix {
    int rows_number;
    int columns_number;

    float* data;

public:
    Matrix(int rows_number, int columns_number);
    ~Matrix();

    int get_rows_number();
    int get_columns_number();

    float get(int row, int column);
    void set(int row, int colunn, float value);

    std::string to_string();

    using one_arg_func = float(*)(float);
    using two_arg_func = float(*)(float, float);

    void multiply(Matrix &rhs, Matrix &result);
    void transpose(Matrix &result);
    void map(one_arg_func f, Matrix& result);
    void combine(Matrix& rhs, two_arg_func , Matrix& result);
    void reduce_row(two_arg_func f);
    void add_column(Matrix& rhs);
    void rows_submatrix(Matrix& result, std::vector<int> indexes, int start, int end);
};

#endif
