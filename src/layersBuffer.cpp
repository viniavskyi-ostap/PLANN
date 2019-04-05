//
// Created by iatsuk on 05.04.2019.
//

#include "layersBuffer.h"

void LayersBuffer::LayersBuffer(int units_number, int batch_size) {
    this->a = Matrix(units_number, batch_size);
    this->da = Matrix(units_number, batch_size);
}