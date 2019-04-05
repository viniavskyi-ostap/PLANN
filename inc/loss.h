//
// Created by ostap on 05.04.19.
//

#ifndef PLANN_LOSS_H
#define PLANN_LOSS_H

#include "matrix.h"

class Loss {
public:
    virtual float compute(Matrix &y_pred, Matrix &y_true) const = 0;
    virtual void compute_derivative(Matrix &y_pred, Matrix &y_true, Matrix &result) const = 0;
};

class MeanSquareError: public Loss{
public:
    float compute(Matrix &y_pred, Matrix &y_true) const override;
    void compute_derivative(Matrix &y_pred, Matrix &y_true, Matrix &result) const override;

private:
    float compute_point(float y_pred, float y_true) const;
    float compute_derivative_point(float y_pred, float y_true) const;
};

#endif //PLANN_LOSS_H
