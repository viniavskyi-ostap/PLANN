//
// Created by iatsuk on 05.04.2019.
//

#include "trainCache.h"


TrainCache::TrainCache(int previous_units_number, int current_units_number, int batch_size) {
    db = new Matrix(current_units_number, 1);
    dw = new Matrix(current_units_number, previous_units_number);
    wt = new Matrix(previous_units_number, current_units_number);
    z = new Matrix(current_units_number, batch_size);
    dz = new Matrix(current_units_number, batch_size);
    at = new Matrix(batch_size, previous_units_number);
}
