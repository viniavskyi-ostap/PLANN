//
// Created by ostap on 17.05.19.
//

#ifndef PLANN_MATRIX_TASKS_H
#define PLANN_MATRIX_TASKS_H

#include "parallel_matrix.h"

void map_task(const std::function<float(float)> &f, Matrix *source,  Matrix *result, int start, int end);

void combine_task(const std::function<float(float, float)> &f, Matrix *source1, Matrix *source2,  Matrix *result, int start, int end);

void map_indexed_task(const std::function<float(float, int, int)> &f, Matrix *source,  Matrix *result, int start, int end);

void transpose_task(Matrix *source, Matrix *result, int start, int end);

void reduce_row_task(std::function<float(float, float)> f, Matrix *source, Matrix *result, float initial_value, int start, int end);

void add_column(Matrix *source, Matrix *rhs, int start, int end);
#endif //PLANN_MATRIX_TASKS_H
