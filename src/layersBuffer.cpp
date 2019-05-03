//
// Created by iatsuk on 05.04.2019.
//

#include "layersBuffer.h"

FitLayersBuffer::FitLayersBuffer(int units_number, int batch_size) {
    a = new Matrix(units_number, batch_size);
    da = new Matrix(units_number, batch_size);
}

FitLayersBuffer::~FitLayersBuffer() {
    delete a;
    delete da;
}

PredictLayersBuffer::PredictLayersBuffer(int units_number, int batch_size) {
    a = new Matrix(units_number, batch_size);
}

PredictLayersBuffer::~PredictLayersBuffer() {
    delete a;
}