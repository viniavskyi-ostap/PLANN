#ifndef PLANN_MATRIX_H
#define PLANN_MATRIX_H

#include <vector>
#include <string>

class Matrix {
    int rows_number;
    int columns_number;

    float* data;

public:
    Matrix() = default;
    Matrix(int rows_number, int columns_number);
//    ~Matrix();

    int get_rows_number() const;
    int get_columns_number() const;

    float get(int row, int column) const;
    void set(int row, int column, float value);

    std::string to_string();

    using one_arg_func = float(*)(float);
    using two_arg_func = float(*)(float, float);

    void multiply(Matrix &rhs, Matrix &result) const;
    void transpose(Matrix &result) const;
//    void map(one_arg_func f, Matrix& result) const;
//    void combine(Matrix& rhs, two_arg_func , Matrix& result) const;
//    void reduce_row(two_arg_func f, Matrix& result) const;
//    void add_column(Matrix& rhs);
//    void rows_submatrix(Matrix& result, std::vector<int> indexes, int start, int end) const;
};

#endif
