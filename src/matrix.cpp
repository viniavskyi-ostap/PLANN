#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "matrix.h"


Matrix::Matrix(int rows_number, int columns_number) {
    this->rows_number = rows_number;
    this->columns_number = columns_number;

    data = new float[rows_number * columns_number];
}

Matrix::Matrix(const Matrix &o) : rows_number(o.rows_number), columns_number(o.columns_number) {
    data = new float[rows_number * columns_number];

    for (int i = 0; i < rows_number; ++i) {
        for (int j = 0; j < columns_number; ++j) {
            set(i, j, o.get(i, j));
        }
    }
}

Matrix::~Matrix() {
    delete[] data;
}

int Matrix::get_rows_number() const {
    return rows_number;
}

int Matrix::get_columns_number() const {
    return columns_number;
}

std::string Matrix::to_string() {
    std::ostringstream ss;

    for (int row = 0; row < rows_number; ++row) {
        ss << '|';
        for (int column = 0; column < columns_number; ++column) {
            ss << std::setw(7) << data[columns_number * row + column] << " ";
        }
        ss << "|\n";
    }

    return ss.str();
}

void Matrix::multiply(const Matrix *rhs, Matrix *result) const {
    for (int row = 0; row < result->rows_number; ++row) {
        for (int column = 0; column < result->columns_number; ++column) {
            result->set(row, column, 0);
        }

        for (int k = 0; k < columns_number; ++k) {
            float this_value = data[row * rows_number + k];

            for (int column = 0; column < result->columns_number; ++column) {
                result->data[row * result->columns_number + column] +=
                        this_value * rhs->data[k * rhs->columns_number + column];
            }
        }
    }
}

void Matrix::transpose(Matrix *result) const {
    if (columns_number != result->rows_number || rows_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    for (int row = 0; row < result->rows_number; ++row) {
        for (int column = 0; column < result->columns_number; ++column) {
            result->set(row, column, get(column, row));
        }
    }
}

void Matrix::map(std::function<float(float)> f, Matrix *result) const {
    if (rows_number != result->rows_number || columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    int size = rows_number * columns_number;
    for (int i = 0; i < size; ++i) {
        result->data[i] = f(data[i]);
    }
}

void Matrix::map_indexed(const float (*f)(float, int, int), Matrix *result) const {
    if (rows_number != result->rows_number || columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    for (int i = 0; i < rows_number; ++i) {
        for (int j = 0; j < columns_number; ++j) {
            result->set(i, j, f(get(i, j), i, j));
        }
    }
}

void Matrix::combine(Matrix *rhs, std::function<float(float, float)> f, Matrix *result) const {
    if (rows_number != rhs->rows_number || columns_number != rhs->columns_number ||
        rows_number != result->rows_number ||
        columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    int size = rows_number * columns_number;
    for (int i = 0; i < size; ++i) {
        result->data[i] = f(data[i], rhs->data[i]);
    }
}

void Matrix::reduce_row(std::function<float(float, float)> f, Matrix *result, float initial_value) const {
    if (rows_number != result->rows_number || result->columns_number != 1) {
        throw std::invalid_argument("Result must be a column vector with number of rows equal to matrices's.");
    }

    float current_result;
    for (int row = 0; row < rows_number; ++row) {
        current_result = initial_value;

        for (int column = 0; column < columns_number; ++column) {
            current_result = f(current_result, get(row, column));
        }

        result->set(row, 0, current_result);
    }
}

void Matrix::add_column(Matrix *rhs) {
    if (rhs->columns_number != 1 || rows_number != rhs->rows_number) {
        throw std::invalid_argument("Right hand side should be a column vector.");
    }

    int size = rows_number * columns_number;
    for (int i = 0; i < size; ++i) {
        data[i] += rhs->data[i / columns_number];
    }
}

// [start, end)
void Matrix::rows_submatrix(Matrix *result, std::vector<int> indexes, int start, int end) const {
    if (columns_number != result->columns_number || (end - start) != result->rows_number) {
        throw std::invalid_argument("Could't create a matrix because of dimensions mismatch.");
    }

    int current_row;
    for (int i = 0; i + start < end; ++i) {
        current_row = indexes[i + start];
        std::copy(data + current_row * columns_number, data + (current_row + 1) * columns_number,
                  result->data + columns_number * i);
    }
}

float Matrix::sum() const {
    float result = 0;

    for (int row = 0; row < rows_number; ++row) {
        for (int column = 0; column < columns_number; ++column) {
            result += get(row, column);
        }
    }

    return result;
}
