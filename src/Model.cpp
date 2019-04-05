#include "plann.h"

using namespace plann;

Model::Model(int input_size, std::vector<Layer>& layers) {
    this->input_size = input_size;
    this->layers = layers;
}
