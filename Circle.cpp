//
// Created by oguzh on 4.12.2025.
//

#include "Circle.h"

#include <iostream>
#include <__msvc_ostream.hpp>
static constexpr double PI = 3.14159265358979323846;

Circle::Circle(double r) :  radius(r) {
    buffer = new double[10];
}
 double Circle::area() const {
     return PI*radius*radius;
 }

void Circle::draw() const {
    std::cout << "Drawing Circle" << std::endl;
}

Circle::~Circle() {
    std::cout << "Circle destructor called\n";
    delete[] buffer;
}


