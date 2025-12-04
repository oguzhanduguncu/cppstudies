//
// Created by oguzh on 4.12.2025.
//

#include "ShapeFactory.h"

#include "Circle.h"
#include "Rectangle.h"


std::unique_ptr<Shape> ShapeFactory::create(const std::string &type, double a, double b) {
    if (type == "circle") {
        return std::make_unique<Circle>(a);
    }
    if (type == "rectangle") {
        return std::make_unique<Rectangle>(a,b);
    }
    return nullptr;
}
