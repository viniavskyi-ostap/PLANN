//
// Created by iatsuk on 05.04.2019.
//

#include "trainCache.h"


TrainCache::TrainCache(int previous_units_number, int current_units_number, int batch_size) {
    w = Matrix(previous_units_number, current_units_number);
    dw = Matrix(previous_units_number, current_units_number);
    wt = Matrix(current_units_number, previous_units_number);
    z = Matrix(current_units_number, batch_size);
    dz = Matrix(current_units_number, batch_size);
    at = Matrix(batch_size, current_units_number);
}
