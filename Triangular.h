//
// Created by oguzh on 4.12.2025.
//

#ifndef TRIANGULAR_H
#define TRIANGULAR_H
#include "Shape.h"


class Triangular : public Shape {
    double base;
    double height;
public:
    Triangular(double a,double b);
    double area() const override;
    void draw() const override;
    ~Triangular() = default;
};



#endif //TRIANGULAR_H
