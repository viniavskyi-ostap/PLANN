//
// Created by User on 4/5/2019.
//

#ifndef PLANN_MODEL_H
#define PLANN_MODEL_H

#include <vector>
#include "layer.h"
#include "loss.h"


class Model {
private:
    std::vector<Layer *> layers;
    int input_size;

    template<typename T>
    std::vector<T *> create_layers_buffer(int batch_size);

public:
    Model(int input_size, std::vector<Layer *> layers);

    ~Model();

    void fit(Matrix *x, Matrix *y, int batch_size, float rate, int epochs, std::string loss_func_name);

    Matrix predict(Matrix *x);

    void init_weights();
};

#endif //PLANN_MODEL_H
