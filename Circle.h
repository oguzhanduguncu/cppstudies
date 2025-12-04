//
// Created by oguzh on 4.12.2025.
//

#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"


class Circle : public Shape {
double radius;
double *buffer;
    public:
    Circle(double r);
    double area() const override;
    void draw() const override;
    ~Circle();
};



#endif //CIRCLE_H
