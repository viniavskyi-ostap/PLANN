//
// Created by User on 4/5/2019.
//

#ifndef PLANN_LOSS_H
#define PLANN_LOSS_H

#include "parallelMatrix.h"


class Loss {
public:
    virtual float compute(Matrix *y_predicted, Matrix *y_true, Matrix *result) const = 0;

    virtual void compute_derivative(Matrix *y_predicted, Matrix *y_true, Matrix *result) const = 0;

    virtual ~Loss() = default;

};


class LossFactory {
public:
    LossFactory() = delete;

    static Loss *get_loss(std::string &name);
};


class MeanSquareError : public Loss {
public:
    float compute(Matrix *y_predicted, Matrix *y_true, Matrix *result) const override;

    void compute_derivative(Matrix *y_predicted, Matrix *y_true, Matrix *result) const override;
};

class CategoricalCrossEntropy : public Loss {
    void softmax(Matrix *x, Matrix *y_pred) const;

public:
    float compute(Matrix *y_predicted, Matrix *y_true, Matrix *result) const override;

    void compute_derivative(Matrix *y_predicted, Matrix *y_true, Matrix *result) const override;
};

#endif //PLANN_LOSS_H
