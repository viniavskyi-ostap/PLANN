#include "parallel_matrix.h"
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <matrix_tasks.h>
#include <mutex>


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
    for (int i = 0; i < result->rows_number; ++i) {
        thread_pool.submit([f, this, result, i]() { map_task(f, this, result, i, i + 1); });
    }
    thread_pool.wait();
}


void Matrix::multiply(Matrix *rhs, Matrix *result) const {
    for (int i = 0; i < result->rows_number; ++i) {
        thread_pool.submit([this, rhs, result, i]() { multiply_task(this, rhs, result, i, i + 1); });
    }
    thread_pool.wait();
}


void Matrix::transpose(Matrix *result) const {
    for (int i = 0; i < result->rows_number; ++i) {
        thread_pool.submit([this, result, i]() { transpose_task(this, result, i, i + 1); });
    }
    thread_pool.wait();
}

void Matrix::map_indexed(const float (*f)(float, int, int), Matrix *result) const {
    for (int i = 0; i < result->rows_number; ++i) {
        thread_pool.submit([f, this, result, i]() { map_indexed_task(f, this, result, i, i + 1); });
    }
    thread_pool.wait();
}

void Matrix::combine(Matrix *rhs, std::function<float(float, float)> f, Matrix *result) const {
    for (int i = 0; i < result->rows_number; ++i) {
        thread_pool.submit([f, this, rhs, result, i]() { combine_task(f, this, rhs, result, i, i + 1); });
    }
    thread_pool.wait();
}

void Matrix::reduce_row(std::function<float(float, float)> f, Matrix *result, float initial_value) const {
    for (int i = 0; i < result->rows_number; ++i) {
        thread_pool.submit(
                [f, this, result, initial_value, i]() { reduce_row_task(f, this, result, initial_value, i, i + 1); });
    }
    thread_pool.wait();
}

void Matrix::add_column(Matrix *rhs) {
    for (int i = 0; i < this->rows_number; ++i) {
        thread_pool.submit(
                [this, rhs, i]() { add_column_task(this, rhs, i, i + 1); });
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

    for (int i = 0; i < this->rows_number; ++i) {
        thread_pool.submit(
                [this, &mutex, &result, i]() { sum_task(this, mutex, result, i, i + 1); });
    }
    thread_pool.wait();

    return result;
}
