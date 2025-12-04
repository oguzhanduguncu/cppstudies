//
// Created by oguzh on 4.12.2025.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Shape.h"


class Rectangle : public Shape {
    double width;
    double height;
    public:
    Rectangle(double w, double h);
    double area() const override;
    void draw() const override;
    ~Rectangle() = default;
};



#endif //RECTANGLE_H
