#include "layer.h"
#include <random>
#include <iostream>


Layer::Layer(int units_number, std::string activation_func) {
    this->units_number = units_number;
    this->activation_func = ActivationFactory::get_activation(activation_func);
}

Layer::~Layer() {
    delete w;
    delete b;
    delete activation_func;
}

void Layer::init_weights(int previous_units_number) {
    w = new Matrix(units_number, previous_units_number);
    b = new Matrix(units_number, 1);

    std::default_random_engine generator;
    std::normal_distribution<float> standard_normal(0.001, 0.05);

    for (int row = 0; row < w->get_rows_number(); ++row) {
        for (int column = 0; column < w->get_columns_number(); ++column) {
            w->set(row, column, standard_normal(generator));
        }
        b->set(row, 0, 0);
    }
}

void Layer::init_train_cache(int batch_size) {
    cache = new TrainCache(w->get_columns_number(), units_number, batch_size);
}

void Layer::clear_train_cache() {
    delete cache;
}

void Layer::forward(FitLayersBuffer *prev, FitLayersBuffer *next) {
    w->multiply(prev->a, cache->z);
//    std::cout << "w: " << this->w->to_string() << std::endl;
    cache->z->add_column(b);
//    std::cout << "z: " << this->cache->z->to_string() << std::endl;

    activation_func->compute(cache->z, next->a);
//    std::cout << "X size: " << prev->a->get_columns_number() << "  " << prev-> a->get_rows_number() << std::endl;
//    std::cout << "X: " << prev->a->to_string() << std::endl;
//    std::cout << "b: " << this->b->to_string() << std::endl;
//    std::cout << "A: " << next->a->to_string() << std::endl;
}

void Layer::forward(PredictLayersBuffer *prev, PredictLayersBuffer *next) {
    w->multiply(prev->a, next->a);
    next->a->add_column(b);
    activation_func->compute(next->a, next->a);
}

void Layer::backward(FitLayersBuffer *prev, FitLayersBuffer *next) {
    int m = cache->z->get_columns_number();

    // Calculating dz
    activation_func->compute_derivative(cache->z, cache->z);
    next->da->combine(cache->z, [](float x, float y) { return x * y; }, cache->dz);

    // Calculating dW
    prev->a->transpose(cache->at);
    cache->dz->multiply(cache->at, cache->dw);
    cache->dw->map([m](float x) { return x / m; }, cache->dw);

    // Calculating db
    cache->dz->reduce_row([](float x, float y) { return x + y; }, cache->db, 0);
    cache->db->map([m](float x) { return x / m; }, cache->db);

    // Calculating dA
    w->transpose(cache->wt);
    cache->wt->multiply(cache->dz, prev->da);
}

int Layer::get_units_number() {
    return units_number;
}

void Layer::update_weights(float rate) {
    cache->dw->map([rate](float x) { return rate * x; }, cache->dw);
    cache->db->map([rate](float x) { return rate * x; }, cache->db);

    w->combine(cache->dw, [](float x, float y) { return x - y; }, w);
    b->combine(cache->db, [](float x, float y) { return x - y; }, b);
}
