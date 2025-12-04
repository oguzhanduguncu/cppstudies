//
// Created by oguzh on 4.12.2025.
//

#include "Rectangle.h"

#include <iostream>
#include <__msvc_ostream.hpp>

#include "Shape.h"

Rectangle::Rectangle(double w, double h) : width(w), height(h) {};

double Rectangle::area() const {
    return width * height;
}

void Rectangle::draw() const {
    std::cout << "Drawing Rectangle" << std::endl;
}




