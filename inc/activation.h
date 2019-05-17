//
// Created by ostap on 05.04.19.
//

#ifndef PLANN_ACTIVATION_H
#define PLANN_ACTIVATION_H

#include "parallel_matrix.h"

class Activation {
public:
    virtual void compute(Matrix *input, Matrix *result) const = 0;

    virtual void compute_derivative(Matrix *input, Matrix *result) const = 0;

    virtual ~Activation() = default;
};

class ActivationFactory {
public:
    ActivationFactory() = delete;

    static Activation *get_activation(std::string &name);
};

class SigmoidActivation : public Activation {
public:
    void compute(Matrix *input, Matrix *result) const override;

    void compute_derivative(Matrix *input, Matrix *result) const override;

private:
    static float compute_point(float x);

    static float compute_derivative_point(float x);
};


class ReluActivation : public Activation {
public:
    void compute(Matrix *input, Matrix *result) const override;

    void compute_derivative(Matrix *input, Matrix *result) const override;

private:
    static float compute_point(float x);

    static float compute_derivative_point(float x);
};

class LinearActivation : public Activation {
public:
    void compute(Matrix *input, Matrix *result) const override;

    void compute_derivative(Matrix *input, Matrix *result) const override;

private:
    static float compute_point(float x);

    static float compute_derivative_point(float x);
};


#endif //PLANN_ACTIVATION_H
