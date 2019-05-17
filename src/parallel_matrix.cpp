#include "parallel_matrix.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <matrix_tasks.h>
#include <mutex>
#include <cmath>

#define WORK_AMOUNT (1e5)
#define WORK_AMOUNT_BY_ROWS(matrix) (floor(WORK_AMOUNT / matrix->columns_number))

ThreadPool Matrix::thread_pool;

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

Matrix::Matrix(int rows_number,  int columns_number, float *array) {
    data = new float[rows_number * columns_number];
    this->rows_number = rows_number;
    this->columns_number = columns_number;

    for (int i = 0; i < rows_number; ++i) {
        for (int j = 0; j < columns_number; ++j) {
            set(i, j, array[i * columns_number + j]);
        }
    }
}

Matrix::~Matrix() {
    delete[] data;
}

inline float Matrix::get(int row, int column) const {
    return data[columns_number * row + column];
}

inline void Matrix::set(int row, int column, float value) {
    data[columns_number * row + column] = value;
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


void Matrix::map(std::function<float(float)> f, Matrix *result) const {
    if (rows_number != result->rows_number || columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < result->rows_number; ++start) {
        int end = start + k;
        end = end > result->rows_number ? result->rows_number : end;

        thread_pool.submit([f, this, result, start, end]() { map_task(f, this, result, start, end); });
    }
    thread_pool.wait();
}


void Matrix::multiply(Matrix *rhs, Matrix *result) const {
    if (columns_number != rhs->rows_number ||
        rows_number != result->rows_number ||
        rhs->columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    int k = floor(WORK_AMOUNT / (this->columns_number * rhs->rows_number));

    for (int start = 0; start < result->rows_number; ++start) {
        int end = start + k;
        end = end > result->rows_number ? result->rows_number : end;
        thread_pool.submit([this, rhs, result, start, end]() { multiply_task(this, rhs, result, start, end); });
    }
    thread_pool.wait();
}


void Matrix::transpose(Matrix *result) const {
    if (columns_number != result->rows_number || rows_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < result->rows_number; ++start) {
        int end = start + k;
        end = end > result->rows_number ? result->rows_number : end;

        thread_pool.submit([this, result, start, end]() { transpose_task(this, result, start, end); });
    }
    thread_pool.wait();
}

void Matrix::map_indexed(const float (*f)(float, int, int), Matrix *result) const {
    if (rows_number != result->rows_number || columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }


    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < result->rows_number; ++start) {
        int end = start + k;
        end = end > result->rows_number ? result->rows_number : end;

        thread_pool.submit([f, this, result, start, end]() { map_indexed_task(f, this, result, start, end); });
    }
    thread_pool.wait();
}

void Matrix::combine(Matrix *rhs, std::function<float(float, float)> f, Matrix *result) const {
    if (rows_number != rhs->rows_number || columns_number != rhs->columns_number ||
        rows_number != result->rows_number ||
        columns_number != result->columns_number) {
        throw std::invalid_argument("Matrix sizes don't match.");
    }

    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < result->rows_number; ++start) {
        int end = start + k;
        end = end > result->rows_number ? result->rows_number : end;

        thread_pool.submit([f, this, rhs, result, start, end]() { combine_task(f, this, rhs, result, start, end); });
    }
    thread_pool.wait();
}

void Matrix::reduce_row(std::function<float(float, float)> f, Matrix *result, float initial_value) const {
    if (rows_number != result->rows_number || result->columns_number != 1) {
        throw std::invalid_argument("Result must be a column vector with number of rows equal to matrices's.");
    }

    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < result->rows_number; ++start) {
        int end = start + k;
        end = end > result->rows_number ? result->rows_number : end;

        thread_pool.submit(
                [f, this, result, initial_value, start, end]() {
                    reduce_row_task(f, this, result, initial_value, start, end);
                });
    }
    thread_pool.wait();
}

void Matrix::add_column(Matrix *rhs) {
    if (rhs->columns_number != 1 || rows_number != rhs->rows_number) {
        throw std::invalid_argument("Right hand side should be a column vector.");
    }

    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < this->rows_number; ++start) {
        int end = start + k;
        end = end > this->rows_number ? this->rows_number : end;

        thread_pool.submit(
                [this, rhs, start, end]() { add_column_task(this, rhs, start, end); });
    }
    thread_pool.wait();
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
    std::mutex mutex;
    float result = 0;

    int k = WORK_AMOUNT_BY_ROWS(this);

    for (int start = 0; start < this->rows_number; ++start) {
        int end = start + k;
        end = end > this->rows_number ? this->rows_number : end;

        thread_pool.submit(
                [this, &mutex, &result, start, end]() { sum_task(this, mutex, result, start, end); });
    }
    thread_pool.wait();

    return result;
}
