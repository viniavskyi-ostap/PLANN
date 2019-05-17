//
// Created by iatsuk on 05.04.2019.
//

#ifndef PLANN_LAYERSBUFFER_H
#define PLANN_LAYERSBUFFER_H

#include "parallel_matrix.h"

class FitLayersBuffer {
public:
    FitLayersBuffer(int units_number, int batch_size);

    ~FitLayersBuffer();

    Matrix *a;
    Matrix *da;
};

class PredictLayersBuffer {
public:
    PredictLayersBuffer(int units_number, int batch_size);

    ~PredictLayersBuffer();

    Matrix *a;
};

#endif //PLANN_LAYERSBUFFER_H
