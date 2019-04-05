#include "matrix.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>


Matrix::Matrix (int rows_number, int columns_number) {
    this->rows_number = rows_number;
    this->columns_number = columns_number;

    data = new float[rows_number * columns_number];
}

inline float Matrix::get(int row, int column) {
    return data[columns_number * row + column];
}

inline void Matrix::set(int row, int column, float value) {
    data[columns_number * row + column] = value;
}

int Matrix::get_rows_number() {
    return rows_number;
}
int Matrix::get_columns_number() {
    return columns_number;
}

std::string Matrix::to_string() {
    std::ostringstream ss;

    for (int row = 0; row < rows_number; ++row) {
        ss << '|';
        for (int column = 0; column < columns_number; ++column) {
            ss << std::setw(10) << data[columns_number * row + column];
        }
        ss << "|\n";
    }

    return ss.str();
}


void Matrix::multiply(Matrix& rhs, Matrix& result) {
    if (columns_number != rhs.rows_number ||
    rows_number != result.rows_number ||
    rhs.columns_number != result.columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    for (int row = 0; row < result.rows_number; row++) {
        for (int column = 0; column < result.columns_number; column++) {
            float value = 0;

            for (int k = 0; k < result.rows_number; k++) {
                value += get(row, k) * rhs.get(k, column);
            }

            result.set(row, column, value);
        }
    }
}

void Matrix::transpose(Matrix& result) {
    if (columns_number != result.rows_number || rows_number != result.columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    for (int row = 0; row < result.rows_number; ++row) {
        for (int column = 0; column < result.columns_number; ++columns_number) {
            result.set(row, column, get(column, row));
        }
    }
}


