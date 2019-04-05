//
// Created by User on 4/5/2019.
//

#include "model.h"

Model::Model(int input_size, std::vector<Layer *>& layers) {
    this->layers = layers;
}

//std::vector<LayersBuffer *> Model::create_layers_buffer() {
//
//}