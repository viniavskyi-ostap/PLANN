#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include <random>
#include <algorithm>
#include "plann.h"

int main() {
    Model m(4, std::vector<Layer *>{
            new Layer(4, "relu"),
            new Layer(8, "relu"),
            new Layer(4, "relu"),
            new Layer(2, "linear")}
    );

    std::default_random_engine generator;
    std::normal_distribution<float> standard_normal(5, 0.0001);

    Matrix x(10, 4);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 4; ++j) {
            x.set(i, j, j);
        }
    }
    for (int i = 5; i < 10; ++i) {
        for (int j = 0; j < 4; ++j) {
            x.set(i, j, j + 10);
        }
    }

    std::cout << x.to_string() << std::endl;
    Matrix y(10, 2);
    for (int i = 0; i < 5; ++i) {
        y.set(i, 0, 0);
        y.set(i, 1, 1);
    }
    for (int i = 5; i < 10; ++i) {
        y.set(i, 0, 1);
        y.set(i, 1, 0);
    }

    std::cout << y.to_string() << std::endl;

    m.fit(&x, &y, 10, 0.1, 10000, "categorical-cross-entropy");

    Matrix in(1, 4);
    for (int i = 0; i < 4; i++) {
        in.set(0, i, i);
    }
    Matrix out = m.predict(&in);
    std::cout << "Result: " << softmax(out).to_string() << std::endl;
}
