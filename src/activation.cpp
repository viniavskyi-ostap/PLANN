#include <cmath>
#include "activation.h"

Activation* ActivationFactory::get_activation(std::string& name){
    if (name == "sigmoid") {
        return new SigmoidActivation();
    }
    else if (name == "relu") {
        return new ReluActivation();
    }
    else if (name == "linear") {
        return new LinearActivation();
    }
    else if (name == "softmax") {
        return new SoftmaxActivation();
    }

    throw std::invalid_argument(name + " is invalid activation function.");
}

float SigmoidActivation::compute_point(float x) {
    return 1 / (1 + exp(-x));
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
