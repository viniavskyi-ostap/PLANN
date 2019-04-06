//
// Created by User on 4/5/2019.
//


#include <iostream>
#include "loss.h"

float MeanSquareError::compute(Matrix &y_predicted, Matrix &y_true, Matrix &result) const {
    y_predicted.combine(y_true, [](float x, float y) { return (x - y) * (x - y); }, result);

    int m = y_predicted.get_columns_number();
    result.map([m](float x) { return x / m; }, result);

    float res = 0;
    for (int row = 0; row < result.get_rows_number(); ++row) {
        for (int column = 0 ; column < result.get_columns_number(); ++column) {
            res += result.get(row, column);
        }
    }

    return res;
}

void MeanSquareError::compute_derivative(Matrix &y_predicted, Matrix &y_true, Matrix &result) const {
    y_predicted.combine(y_true, [](float x, float y) { return x - y; }, result);
}
