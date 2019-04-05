#include <cmath>
#include "activation.h"


float SigmoidActivation::compute(float x) {
    return 1 / (1 + exp(-x));
}

float SigmoidActivation::compute_derivative(float x) {
    return x * (1 - x);
}

float ReluActivation::compute(float x) {
    return x > 0 ? x : 0;
}

float ReluActivation::compute_derivative(float x) {
    return x > 0 ? 1 : 0;
}

float LinearActivation::compute(float x) {
    return x;
}

float LinearActivation::compute_derivative(float x) {
    return 1;
}