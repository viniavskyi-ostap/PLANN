//
// Created by iatsuk on 05.04.2019.
//

#ifndef PLANN_LAYERSBUFFER_H
#define PLANN_LAYERSBUFFER_H

#include "matrix.h"

class LayersBuffer {
public:
    LayersBuffer(int units_number, int batch_size);

    Matrix *a;
    Matrix *da;
};

#endif //PLANN_LAYERSBUFFER_H
