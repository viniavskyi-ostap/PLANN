#include <iostream>
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
    }

    throw std::invalid_argument(name + " is invalid loss function name.");
}
