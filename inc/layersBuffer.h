//
// Created by iatsuk on 05.04.2019.
//

#ifndef PLANN_LAYERSBUFFER_H
#define PLANN_LAYERSBUFFER_H

#include "matrix.h"

class LayersBuffer {
    Matrix a;
    Matrix da;

public:
    void LayersBuffer(int units_number, int batch_size);
};

#endif //PLANN_LAYERSBUFFER_H
