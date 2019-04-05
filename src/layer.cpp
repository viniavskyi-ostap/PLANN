//
// Created by iatsuk on 05.04.2019.
//

#include "layer.h"

Layer::Layer(int units_number, Activation* activation_func) {
    units_number = units_number;
    activation_func = activation_func;
}

Layer::~Layer() {
    delete cache;
}

void Layer::init_weights(int previous_units_number) {
    w = Matrix(previous_units_number, units_number);
    b = Matrix(previous_units_number, 1);
}

void Layer::init_train_cache(int batch_size) {
    cache = new TrainCache(w.get_rows_number(), units_number, batch_size);
}

void Layer::clear_train_cache() {
    delete cache;
}

void Layer::forward(LayersBuffer *prev, LayersBuffer *next) {
    w.multiply(prev->a, cache->z);
    cache->z.add_column(b);
    activation_func->compute(cache->z, next->a);
}

void Layer::backward(LayersBuffer *prev, LayersBuffer *next) {
    activation_func->compute_derivative(cache->z, cache->z);
    next->da.combine(cache->z, [](float x, float y) {return x * y;}, cache->dz);
    prev->a.transpose(cache->at);
    cache->z.multiply(cache->at, cache->dw);

    int m = cache->z.get_columns_number();
    cache->dw.map([m](float x) {return x / m;}, cache->dw);

    cache->dz.reduce_row([](float x, float y) {return x + y;}, cache->db);
    cache->db.map([m](float x) {return x / m;}, cache->db);
    w.transpose(cache->wt);
    cache->wt.multiply(cache->dz, prev->da);
}

int Layer::get_units_number() {
    return units_number;
}
