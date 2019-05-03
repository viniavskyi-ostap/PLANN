#include <iostream>
#include <cmath>
#include "loss.h"


float MeanSquareError::compute(Matrix *y_predicted, Matrix *y_true, Matrix *result) const {
    y_predicted->combine(y_true, [](float x, float y) { return (x - y) * (x - y); }, result);

    int m = y_predicted->get_columns_number();
    return result->sum() / (2 * m);
}

void MeanSquareError::compute_derivative(Matrix *y_predicted, Matrix *y_true, Matrix *result) const {
    y_predicted->combine(y_true, [](float x, float y) { return x - y; }, result);
}

Loss *LossFactory::get_loss(std::string &name) {
    if (name == "mse") {
        return new MeanSquareError();
    } else if (name == "categorical-cross-entropy") {
        return new CategoricalCrossEntropy();
    }

    throw std::invalid_argument(name + " is invalid loss function name.");
}

float CategoricalCrossEntropy::compute(Matrix *y_predicted, Matrix *y_true, Matrix *result) const {
    softmax(y_predicted, result);
    result->combine(y_true, [](float y_pred, float y) { return y * std::log(y_pred); }, result);
    return -result->sum() / result->get_columns_number();
}

void CategoricalCrossEntropy::compute_derivative(Matrix *y_predicted, Matrix *y_true, Matrix *result) const {
    softmax(y_predicted, result);
    result->combine(y_true, [](float y_pred, float y) { return y_pred - y; }, result);
}

void CategoricalCrossEntropy::softmax(Matrix *x, Matrix *result) const {
    x->map([](float v) { return expf(v); }, result);

    for (int j = 0; j < result->get_columns_number(); ++j) {
        float col_sum = 0;
        for (int i = 0; i < result->get_rows_number(); ++i) {
            col_sum += result->get(i, j);
        }

        for (int i = 0; i < result->get_rows_number(); ++i) {
            result->set(i, j, result->get(i, j) / col_sum);
        }
    }
}
