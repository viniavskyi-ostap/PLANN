//
// Created by ostap on 17.05.19.
//

#ifndef PLANN_PARALLEL_MATRIX_H
#define PLANN_PARALLEL_MATRIX_H

#include <vector>
#include <string>
#include <functional>

class Matrix {
    int rows_number;
    int columns_number;

    float *data;

public:
    Matrix() = default;

    Matrix(int rows_number, int columns_number);

    Matrix(const Matrix &other);

    ~Matrix();

    int get_rows_number() const;

    int get_columns_number() const;

    float get(int row, int column) const;

    void set(int row, int column, float value);

    std::string to_string();

    void multiply(Matrix *rhs, Matrix *result) const;

    void optimised_multiply(const Matrix *rhs, Matrix *result) const;

    void transpose(Matrix *result) const;

    void map_indexed(const float (*f)(float, int, int), Matrix *result) const;

    void map(std::function<float(float)> f, Matrix *result) const;

    void combine(Matrix *rhs, std::function<float(float, float)> f, Matrix *result) const;

    void reduce_row(std::function<float(float, float)> f, Matrix *result, float initial_value) const;

    void add_column(Matrix *rhs);

    void rows_submatrix(Matrix *result, std::vector<int> indexes, int start, int end) const;

    float sum() const;
};

#endif //PLANN_PARALLEL_MATRIX_H
