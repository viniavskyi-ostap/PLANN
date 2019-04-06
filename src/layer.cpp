//
// Created by iatsuk on 05.04.2019.
//

#include "layer.h"
#include <random>
#include <iostream>


Layer::Layer(int units_number, Activation *activation_func) {
    this->units_number = units_number;
    this->activation_func = activation_func;
}


Layer::~Layer() {
    delete cache;
    delete w;
    delete b;
}

void Layer::init_weights(int previous_units_number) {
    w = new Matrix(units_number, previous_units_number);
    b = new Matrix(units_number, 1);

    std::default_random_engine generator;
    std::normal_distribution<float> standard_normal(2, 1);

    for (int row = 0; row < w->get_rows_number(); ++row) {
        for (int column = 0; column < w->get_columns_number(); ++column) {
            w->set(row, column, 1.1);
        }
        b->set(row, 0, standard_normal(generator));
    }
}

void Layer::init_train_cache(int batch_size) {
    cache = new TrainCache(w->get_columns_number(), units_number, batch_size);
}

void Layer::clear_train_cache() {
    delete cache;
}

void Layer::forward(LayersBuffer *prev, LayersBuffer *next) {
    w->multiply(*prev->a, *cache->z);
    cache->z->add_column(*b);
    activation_func->compute(*cache->z, *next->a);
}

void Layer::backward(LayersBuffer *prev, LayersBuffer *next) {
    activation_func->compute_derivative(*cache->z, *cache->z);
    next->da->combine(*cache->z, [](float x, float y) { return x * y; }, *cache->dz);
    prev->a->transpose(*cache->at);
    cache->z->multiply(*cache->at, *cache->dw);

    int m = cache->z->get_columns_number();
    cache->dw->map([m](float x) { return x / m; }, *cache->dw);

    cache->dz->reduce_row([](float x, float y) { return x + y; }, *cache->db, 0);
    cache->db->map([m](float x) { return x / m; }, *cache->db);
    w->transpose(*cache->wt);
    cache->wt->multiply(*cache->dz, *prev->da);
}

int Layer::get_units_number() {
    return units_number;
}

void Layer::update_weights(float rate) {
    cache->dw->map([rate](float x) { return rate * x; }, *cache->dw);
    cache->db->map([rate](float x) { return rate * x; }, *cache->db);

    w->combine(*cache->dw, [](float x, float y) { return x - y; }, *w);
    b->combine(*cache->db, [](float x, float y) { return x - y; }, *b);
}
