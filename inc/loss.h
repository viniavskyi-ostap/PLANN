//
// Created by User on 4/5/2019.
//

#ifndef PLANN_LOSS_H
#define PLANN_LOSS_H

#include "matrix.h"

class Loss {
private:
    float compute(Matrix &y_pred, Matrix &y_true);

    void compute_derivative(Matrix &x, Matrix &y, Matrix &result);

};

#endif //PLANN_LOSS_H
