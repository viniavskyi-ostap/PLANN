//
// Created by iatsuk on 05.04.2019.
//

#include "layer.h"

void Layer::Layer(int units_number, Activation activation_func) {
    this->units_number = units_number;
    this->activation_func = activation_func;
}

void Layer::init_weights(int previous_units_number) {
    this->w = Matrix(previous_units_number, this->units_number);
    this->b = Matrix(previous_units_number, 1);
}

void Layer::init_train_cache(int batch_size) {
    this->cache = TrainCache(this->w.get_rows_number(), this->units_number, batch_size);
}

void Layer::clear_train_cache() {
    // ToDo: solve this problem
    this->cache = nullptr;
}