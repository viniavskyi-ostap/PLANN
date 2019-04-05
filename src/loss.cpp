//
// Created by ostap on 05.04.19.
//
#include <cmath>
#include "loss.h"

float MeanSquareError::compute(Matrix &y_pred, Matrix &y_true) const {
//    TODO:
}

void MeanSquareError::compute_derivative(Matrix &y_pred, Matrix &y_true, Matrix &result) const {
//    TODO:
}

float MeanSquareError::compute_point(float y_pred, float y_true) const {
    return pow(y_pred - y_true, 2.0f);
}

float MeanSquareError::compute_derivative_point(float y_pred, float y_true) const {
    return 2 * (y_pred - y_true);
}