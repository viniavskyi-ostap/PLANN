//
// Created by iatsuk on 05.04.2019.
//

#include "trainCache.h"

class trainCache {
    Matrix w;
    Matrix dw;
    Matrix z;
    Matrix dz;
    Matrix at;
    Matrix wt;

public :
    void TrainCache(int previous_units_number, int current_units_number, int batch_size) {
        this->w = new Matrix(previous_units_number, current_units_number);
        this->dw = new Matrix(previous_units_number, current_units_number);
        this->wt = new Matrix(current_units_number, previous_units_number);
        this->z = new Matrix(current_units_number, batch_size);
        this->dz = new Matrix(current_units_number, batch_size);
        this->at = new Matrix(batch_size, current_units_number);
    }
};