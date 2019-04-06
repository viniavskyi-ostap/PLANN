#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include "activation.h"
#include <random>
#include "loss.h"
#include <algorithm>
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

    m.fit(x, y, 2, 0.001f, 2, new MeanSquareError());

}

void test_first() {
    Matrix m1{2, 2}, m2{2, 2}, m3{2, 2};

    m1.set(0, 0, 1);
    m1.set(0, 1, 1);
    m1.set(1, 0, 1);
    m1.set(1, 1, 1);

    m2.set(0, 0, 1);
    m2.set(0, 1, 1);
    m2.set(1, 0, 0);
    m2.set(1, 1, 1);

    m1.multiply(m2, m3);
    std::cout << m3.to_string();
}

void test_second() {

}
