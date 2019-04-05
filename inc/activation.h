//
// Created by ostap on 05.04.19.
//

#ifndef PLANN_ACTIVATION_H
#define PLANN_ACTIVATION_H

#include "matrix.h"

class Activation {
public:
    virtual void compute(Matrix &input, Matrix &result) = 0;

    virtual void compute_derivative(Matrix &input, Matrix &result) = 0;

    virtual ~Activation() = default;
};

class SigmoidActivation : public Activation {
public:
    void compute(Matrix &input, Matrix &result);

    void compute_derivative(Matrix &input, Matrix &result);
};

class SoftmaxActivation : public Activation {
public:
    void compute(Matrix &input, Matrix &result);

    void compute_derivative(Matrix &input, Matrix &result);
};

class ReluActivation : public Activation {
public:
    void compute(Matrix &input, Matrix &result);

    void compute_derivative(Matrix &input, Matrix &result);
};

class LinearActivation : public Activation {
public:
    void compute(Matrix &input, Matrix &result);

    void compute_derivative(Matrix &input, Matrix &result);
};


#endif //PLANN_ACTIVATION_H
