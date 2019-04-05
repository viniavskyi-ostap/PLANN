//
// Created by iatsuk on 05.04.2019.
//

#include "trainCache.h"


void TrainCache::TrainCache(int previous_units_number, int current_units_number, int batch_size) {
    this->w = Matrix(previous_units_number, current_units_number);
    this->dw = Matrix(previous_units_number, current_units_number);
    this->wt = Matrix(current_units_number, previous_units_number);
    this->z = Matrix(current_units_number, batch_size);
    this->dz = Matrix(current_units_number, batch_size);
    this->at = Matrix(batch_size, current_units_number);
}