#include <cmath>
#include "activation.h"

//sigmoid activation
float SigmoidActivation::compute_point(float x) {
    return 1 / (1 + exp(-x));
}

float SigmoidActivation::compute_derivative_point(float x) {
    return x * (1 - x);
}

void SigmoidActivation::compute(Matrix &input, Matrix &result) {
    input.map(result, this->compute_point);
}

void SigmoidActivation::compute_derivative(Matrix &input, Matrix &result) {
    input.map(result, this->compute_derivative_point);
}

// relu activation
float ReluActivation::compute_point(float x) {
    return x > 0 ? x : 0;
}

float ReluActivation::compute_derivative_point(float x) {
    return x > 0 ? 1 : 0;
}

void ReluActivation::compute(Matrix &input, Matrix &result) {
    input.map(result, this->compute_point);
}

void ReluActivation::compute_derivative(Matrix &input, Matrix &result) {
    input.map(result, this->compute_derivative_point);
}

// linear activation
float LinearActivation::compute_point(float x) {
    return x;
}

float LinearActivation::compute_derivative_point(float x) {
    return 1;
}

void LinearActivation::compute(Matrix &input, Matrix &result) {
    input.map(result, this->compute_point);
}

void LinearActivation::compute_derivative(Matrix &input, Matrix &result) {
    input.map(result, this->compute_derivative_point);
}