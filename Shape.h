//
// Created by oguzh on 4.12.2025.
//

#ifndef SHAPE_H
#define SHAPE_H
class Shape {
    public:
    virtual double area() const = 0;
    virtual void draw() const = 0;

    virtual ~Shape() = default;
};
#endif //SHAPE_H
