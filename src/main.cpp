#include <stdio.h>
#include <iostream>
#include <functional>
#include <vector>
#include <random>
#include <algorithm>
#include "plann.h"

void test_first(), test_second();

int main() {
    Model m(4, std::vector<Layer *>{
        new Layer(4, new ReluActivation()),
        new Layer(8, new ReluActivation()),
        new Layer(4, new ReluActivation()),
        new Layer(1, new LinearActivation())}
        );

    std::default_random_engine generator;
    std::normal_distribution<float> standard_normal(5, 0.0001);

    Matrix x(10, 4);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 4; ++j) {
            x.set(i, j, j);
        }
    }
    std::cout << x.to_string() << std::endl;
    Matrix y(10, 1);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 1; ++j) {
            y.set(i, j, x.get(i, j) * 5 + 7);
        }
    }

    std::cout << y.to_string() << std::endl;

    m.fit(x, y, 10, 0.01f, 100, new MeanSquareError());
}
