#include "matrix_tasks.h"


void map_task(const std::function<float(float)> &f, Matrix *source, Matrix *result, int start, int end) {
    int row_size = source->get_columns_number();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < row_size; ++j) {
            result->set(i, j, f(source->get(i, j)));
        }
    }
}

void combine_task(const std::function<float(float, float)> &f, Matrix *source1, Matrix *source2, Matrix *result,
                  int start, int end) {
    int row_size = source1->get_columns_number();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < row_size; ++j) {
            result->set(i, j, f(source1->get(i, j), source2->get(i, j)));
        }
    }
}

void map_indexed_task(const std::function<float(float, int, int)> &f, Matrix *source, Matrix *result,
                      int start, int end) {
    int row_size = source->get_columns_number();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < row_size; ++j) {
            result->set(i, j, f(source->get(i, j), i, j));
        }
    }
}

void transpose_task(Matrix *source, Matrix *result, int start, int end) {
    int row_size = source->get_columns_number();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < row_size; ++j) {
            result->set(j, i, source->get(i, j));
        }
    }
}

void reduce_row_task(std::function<float(float, float)> f, Matrix *source, Matrix *result,
                     float initial_value, int start, int end) {
    int row_size = source->get_columns_number();
    float current_result;

    for (int i = start; i < end; ++i) {
        current_result = initial_value;
        for (int j = 0; j < row_size; ++j) {
            current_result = f(current_result, source->get(i, j));
        }
        result->set(i, 0, current_result);
    }
}

void add_column(Matrix *source, Matrix *rhs, int start, int end) {
    int row_size = source->get_columns_number();
    float current_summand;

    for (int i = start; i < end; ++i) {
        current_summand = rhs->get(i, 0);
        for (int j = 0; j < row_size; ++j) {
            source->set(i, j, source->get(i, j) + current_summand);
        }
    }
}

float sum_task(Matrix *source, int start, int end) {
    int row_size = source->get_columns_number();
    float result = 0;

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < row_size; ++j) {
           result += source->get(i, j);
        }
    }
    return result;
}

void multiply_task(Matrix *source1, Matrix *source2, Matrix *result, int start, int end){
    int source1_row_size = source1->get_columns_number();
    int source2_row_size = source2->get_columns_number();

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < source2_row_size; ++j) {
            result->set(i, j, 0);
        }
    }

    for (int i = start; i < end; ++i) {
        for (int j = 0; j < source1_row_size; ++j) {
            for (int k = 0; k < source2_row_size; ++k) {
                result->set(i, k, result->get(i, k) + source1->get(i, j) * source2->get(j, k));
            }
        }
    }

}