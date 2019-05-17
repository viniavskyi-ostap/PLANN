//
// Created by iatsuk on 05.04.2019.
//

#ifndef PLANN_LAYER_H
#define PLANN_LAYER_H

#include "parallel_matrix.h"
#include "activation.h"
#include "trainCache.h"
#include "layersBuffer.h"


class Layer {
private:
    int units_number;

    Activation *activation_func = nullptr;
    Matrix *b = nullptr;
    Matrix *w = nullptr;
    TrainCache *cache = nullptr;

public:
    Layer(int units_number, std::string name);

    ~Layer();

    void init_weights(int previous_units_number);

    void init_train_cache(int batch_size);

    void clear_train_cache();

    void forward(FitLayersBuffer *prev, FitLayersBuffer *next);

    void forward(PredictLayersBuffer *prev, PredictLayersBuffer *next);

    void backward(FitLayersBuffer *prev, FitLayersBuffer *next);

    int get_units_number();

    void update_weights(float rate);

    // TODO remove
    friend class Model;
};

#endif //PLANN_LAYER_H
