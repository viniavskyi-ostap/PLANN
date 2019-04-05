#include <cmath>
#include "activation.h"

//sigmoid activation
float SigmoidActivation::compute_point(float x) {
    return 1 / (1 + expf(-x));
}

float SigmoidActivation::compute_derivative_point(float x) {
    return x * (1 - x);
}

void SigmoidActivation::compute(Matrix &input, Matrix &result) const {
    input.map(this->compute_point, result);
}

void SigmoidActivation::compute_derivative(Matrix &input, Matrix &result) const {
    input.map(this->compute_derivative_point, result);
}

// ReLU activation
float ReluActivation::compute_point(float x) {
    return x > 0 ? x : 0;
}

float ReluActivation::compute_derivative_point(float x) {
    return x > 0 ? 1 : 0;
}

void ReluActivation::compute(Matrix &input, Matrix &result) const {
    input.map(this->compute_point, result);
}

void ReluActivation::compute_derivative(Matrix &input, Matrix &result) const {
    input.map(this->compute_derivative_point, result);
}

// linear activation
float LinearActivation::compute_point(float x) {
    return x;
}

float LinearActivation::compute_derivative_point(float x) {
    return 1;
}

void LinearActivation::compute(Matrix &input, Matrix &result) const {
    input.map(this->compute_point, result);
}

void LinearActivation::compute_derivative(Matrix &input, Matrix &result) const {
    input.map(this->compute_derivative_point, result);
}

// SoftMax activation
void SoftmaxActivation::compute(Matrix &input, Matrix &result) const {
//    TODO: implement softmax compute
}

void SoftmaxActivation::compute_derivative(Matrix &input, Matrix &result) const {
//    TODO: implement softmax derivative
}