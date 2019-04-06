#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include "activation.h"
#include <random>
#include "loss.h"
#include <algorithm>
#include <loss.h>
#include "model.h"
#include "layer.h"

void test_first(), test_second();

int main() {
    Model m(4, std::vector<Layer *>{new Layer(4, new LinearActivation()),
                                    new Layer(2, new LinearActivation())});

    std::default_random_engine generator;
    std::normal_distribution<float> standard_normal(5, 1);

    Matrix x(4, 4);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            x.set(i, j, standard_normal(generator));
        }
    }

    Matrix y(4, 2);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            y.set(i, j, standard_normal(generator));
        }
    }

    m.fit(x, y, 2, 0.01f, 10, new MeanSquareError());
}

void test_first() {
    Matrix m1{10, 10};

    std::cout << m1.to_string();
}

void test_second() {

}
