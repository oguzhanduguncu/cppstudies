//
// Created by oguzh on 4.12.2025.
//

#include "Triangular.h"

#include <iostream>
#include <__msvc_ostream.hpp>


Triangular::Triangular(double a, double b) :  base(a), height(b) {};

double Triangular::area() const {
    return base * height / 2.0;
}

void Triangular::draw() const {
    std::cout << "Drawing triangular" << std::endl;
}


