//
// Created by iatsuk on 05.04.2019.
//

#include "layersBuffer.h"

LayersBuffer::LayersBuffer(int units_number, int batch_size) {
    a = new Matrix(units_number, batch_size);
    da = new Matrix(units_number, batch_size);
}
