//
// Created by iatsuk on 05.04.2019.
//

#ifndef PLANN_TRAINCASHE_H
#define PLANN_TRAINCASHE_H

#include "matrix.h"

class TrainCache {
public:
    TrainCache() = default;
    TrainCache(int previous_units_number, int current_units_number, int batch_size);
    ~TrainCache();

    Matrix *db;
    Matrix *dw;
    Matrix *z;
    Matrix *dz;
    Matrix *at;
    Matrix *wt;
};

#endif //PLANN_TRAINCASHE_H
