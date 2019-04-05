//
// Created by iatsuk on 05.04.2019.
//

#ifndef PLANN_LAYER_H
#define PLANN_LAYER_H

#include "matrix.h"
#include "activation.h"
#include "trainCache.h"
#include "layersBuffer.h"


class Layer {
private:
    int units_number;

    Activation *activation_func;
    Matrix w;
    Matrix b;
    TrainCache *cache;

public:
    Layer(int units_number, Activation *activation_func);

    ~Layer();

    void init_weights(int previous_units_number);

    void init_train_cache(int batch_size);

    void clear_train_cache();

    void forward(LayersBuffer *prev, LayersBuffer *next);

    void backward(LayersBuffer *prev, LayersBuffer *next);

    int get_units_number();
};

#endif //PLANN_LAYER_H
