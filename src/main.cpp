#include "matrix.h"
#include <stdio.h>
#include <iostream>
#include <functional>

void test_first(), test_second();

class B {
public:
    ~B() {
        std::cout << "B destructor.\n";
    }
};

class A {
public:
    B* b = new B();

    ~A() {
        delete b;
        std::cout << "A destructor\n";
    }
};

void g(std::function<float (float)>& f) {
    std::cout << f(10.0f);
}

float f1(float x) {
    return x + 1;
}

int main() {
    Matrix a(2, 2);
    int i = a.get_columns_number();
    std::cout << ([i](float x) {return x / i;})(10);

    std::function<float (float)> f = [](float x) { return x + 1; };
//    g(f1);
//    std::cout << ">>> Starting tests" << std::endl;
//    std::cout << ">>> Test 1" << std::endl;
//    test_first();
//    std::cout << ">>> Test 2" << std::endl;
//    test_second();
//    std::cout << ">>> End" << std::endl;
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
