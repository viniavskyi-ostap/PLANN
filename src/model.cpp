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

void Model::init_weights() {
    layers[0]->init_weights(input_size);

    for (int i = 1; i < layers.size(); ++i) {
        layers[i]->init_weights(layers[i - 1]->get_units_number());
    }
}

std::vector<LayersBuffer *> Model::create_layers_buffer(int batch_size) {
    std::vector<LayersBuffer *> buffers;
    buffers.reserve(layers.size() + 1);

    buffers.push_back(new LayersBuffer(input_size, batch_size));
    std::for_each(layers.begin(), layers.end(), [&buffers, batch_size](Layer *layer) {
        buffers.push_back(new LayersBuffer(layer->get_units_number(), batch_size));
    });

    return buffers;
}

void Model::fit(Matrix &x, Matrix &y, int batch_size, float rate, int epochs, Loss *loss_func) {
    std::for_each(layers.begin(), layers.end(), [batch_size](Layer *layer) { layer->init_train_cache(batch_size); });
    std::vector<LayersBuffer *> buffers = create_layers_buffer(batch_size);
    Matrix x_batch(batch_size, x.get_columns_number());
    Matrix y_batch(batch_size, y.get_columns_number());

    std::vector<int> indexes;
    std::random_device rd;
    std::mt19937 g(rd());
    indexes.reserve((size_t) x.get_rows_number());
    for (int i = 0; i < x.get_rows_number(); ++i)
        indexes.push_back(i);

    Matrix current_res(layers[layers.size() - 1]->get_units_number(), batch_size);
    for (int i = 0; i < epochs; ++i) {
        float total_loss = 0;
        std::shuffle(indexes.begin(), indexes.end(), g);

        for (int j = 0; j + batch_size <= indexes.size(); j += batch_size) {
            // cut batch matrices
            x.rows_submatrix(x_batch, indexes, j, j + batch_size);
            y.rows_submatrix(y_batch, indexes, j, j + batch_size);
            x_batch.transpose(*buffers[0]->a);

            //forward propagation
            for (int z = 0; z < layers.size(); ++z) {
                layers[z]->forward(buffers[z], buffers[z + 1]);
            }

            // back propagation
            y_batch.transpose(*buffers[buffers.size() - 1]->da);
            total_loss += loss_func->compute(*buffers[buffers.size() - 1]->a, *buffers[buffers.size() - 1]->da,
                                             current_res);
            loss_func->compute_derivative(*buffers[buffers.size() - 1]->a, *buffers[buffers.size() - 1]->da,
                                          *buffers[buffers.size() - 1]->da);
            for (int z = (int) (layers.size() - 1); z >= 0; --z) {
                layers[z]->backward(buffers[z], buffers[z + 1]);
//                *            }

                //update weights
                std::for_each(layers.begin(), layers.end(), [rate](Layer *layer) { layer->update_weights(rate); });
            }

        }

        std::cout <<  "Current total loss: " <<  total_loss << std::endl;
    }
}
