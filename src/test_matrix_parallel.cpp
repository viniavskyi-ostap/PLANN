//
// Created by ostap on 17.05.19.
//

#include <iostream>
#include "parallelMatrix.h"
#include "timeMeasure.h"

const float map_indexed_func(const float x, int i, int j) {
    return x / (i + 1);
}

float map_func(float x) {
    return x * x;
}

float combine_func(float x, float y) {
    return x + y;
}

int main() {
    const int size = 300;
    auto x = Matrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            x.set(i, j, 5 * i + j);
    }

    auto y = Matrix(size, size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            y.set(i, j, i + 7 * j);
    }

    auto z = Matrix(size, 1);
    for (int i = 0; i < size; i++) {
        y.set(i, 0, 2 * i);
    }
    auto result = Matrix(size, size);
    std::cout << "Start" << std::endl;
    // test multiplying
    auto start = get_current_time_fenced();
    x.multiply(&y, &result);

//    std::cout << result.to_string() << std::endl;
    std::cout << "Multiplying: " << to_us(get_current_time_fenced() - start) << std::endl;

    // test transpose
    start = get_current_time_fenced();
    x.transpose(&result);
//    std::cout << result.to_string() << std::endl;
    std::cout << "Transpose: " << to_us(get_current_time_fenced() - start) << std::endl;


    // test map indexed
    start = get_current_time_fenced();
    x.map_indexed(map_indexed_func, &result);
//    std::cout << result.to_string() << std::endl;
    std::cout << "Map indexed: " << to_us(get_current_time_fenced() - start) << std::endl;


    // test map
    start = get_current_time_fenced();
    x.map(map_func, &result);
//    std::cout << result.to_string() << std::endl;
    std::cout << "Map: " << to_us(get_current_time_fenced() - start) << std::endl;


    // test combine
    start = get_current_time_fenced();
    x.combine(&y, combine_func, &result);
//    std::cout << result.to_string() << std::endl;
    std::cout << "Combine: " << to_us(get_current_time_fenced() - start) << std::endl;


    // test reduce_row
    start = get_current_time_fenced();
    x.reduce_row(combine_func, &z, 0);
//    std::cout << z.to_string() << std::endl;
    std::cout << "Reduce row: " << to_us(get_current_time_fenced() - start) << std::endl;


    // test add_column
    start = get_current_time_fenced();
    x.add_column(&z);
//    std::cout << x.to_string() << std::endl;
    std::cout << "Add column: " << to_us(get_current_time_fenced() - start) << std::endl;


    // test sum
    start = get_current_time_fenced();
//    std::cout << result.sum() << std::endl;
    std::cout << "Sum: " << to_us(get_current_time_fenced() - start) << std::endl;
}

