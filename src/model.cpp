#include <algorithm>
#include <random>
#include <iostream>
#include "model.h"


Model::Model(int input_size, std::vector<Layer *> layers) {
    if (layers.empty()) {
        throw std::invalid_argument("Layers must have at least one elements.");
    }

    this->layers = layers;
    this->input_size = input_size;

    init_weights();
}

Model::~Model() {
    for (auto layer: layers) delete layer;
}

void Model::init_weights() {
    layers[0]->init_weights(input_size);

    for (int i = 1; i < layers.size(); ++i) {
        layers[i]->init_weights(layers[i - 1]->get_units_number());
    }
}


template<typename T>
std::vector<T *> Model::create_layers_buffer(int batch_size) {
    std::vector<T *> buffers;
    buffers.reserve(layers.size() + 1);

    buffers.push_back(new T(input_size, batch_size));
    for (auto layer: layers) buffers.push_back(new T(layer->get_units_number(), batch_size));

    return buffers;
}

void Model::fit(Matrix *x, Matrix *y, int batch_size, float rate, int epochs, std::string loss_func_name) {
    Loss *loss_func = LossFactory::get_loss(loss_func_name);

    for (auto layer: layers) layer->init_train_cache(batch_size);
    std::vector<FitLayersBuffer *> buffers = create_layers_buffer<FitLayersBuffer>(batch_size);
    Matrix x_batch(batch_size, x->get_columns_number());
    Matrix y_batch(batch_size, y->get_columns_number());

    std::vector<int> indexes;
    std::random_device rd;
    std::mt19937 g(rd());
    indexes.reserve((size_t) x->get_rows_number());
    for (int i = 0; i < x->get_rows_number(); ++i)
        indexes.push_back(i);

    Matrix current_res(layers[layers.size() - 1]->get_units_number(), batch_size);
    for (int i = 0; i < epochs; ++i) {
        float total_loss = 0;
        std::shuffle(indexes.begin(), indexes.end(), g);

        for (int j = 0; j + batch_size <= indexes.size(); j += batch_size) {
            // cut batch matrices
            x->rows_submatrix(&x_batch, indexes, j, j + batch_size);
            y->rows_submatrix(&y_batch, indexes, j, j + batch_size);
            x_batch.transpose(buffers[0]->a);

            //forward propagation
            for (int z = 0; z < layers.size(); ++z) {
                layers[z]->forward(buffers[z], buffers[z + 1]);
            }

            // back propagation
            y_batch.transpose(&current_res);
            total_loss += loss_func->compute(buffers[buffers.size() - 1]->a, &current_res,
                                             buffers[buffers.size() - 1]->da);
            y_batch.transpose(&current_res);
            loss_func->compute_derivative(buffers[buffers.size() - 1]->a, &current_res,
                                          buffers[buffers.size() - 1]->da);
            for (int z = (int) (layers.size() - 1); z >= 0; --z) {
                layers[z]->backward(buffers[z], buffers[z + 1]);

                //update weights
                for (auto layer: layers) layer->update_weights(rate);
            }

        }

        std::cout << "Current total loss: " << total_loss << std::endl;
    }

    for (auto buffer : buffers) delete buffer;
    for (auto layer: layers) layer->clear_train_cache();
}

Matrix Model::predict(Matrix *x) {
    int size = x->get_rows_number();

    std::vector<PredictLayersBuffer *> buffers = create_layers_buffer<PredictLayersBuffer>(size);

    x->transpose(buffers[0]->a);
    //forward propagation
    for (int i = 0; i < layers.size(); ++i) {
        layers[i]->forward(buffers[i], buffers[i + 1]);
    }

    Matrix *final_buffer = buffers[buffers.size() - 1]->a;
    Matrix result(final_buffer->get_columns_number(), final_buffer->get_rows_number());
    final_buffer->transpose(&result);
    for (auto buffer : buffers) delete buffer;
    return result;
}
