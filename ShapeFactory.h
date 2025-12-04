//
// Created by oguzh on 4.12.2025.
//

#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include "Shape.h"
#include <memory>
#include <string>

class ShapeFactory {
public:
    static std::unique_ptr<Shape> create(const std::string& type, double a, double b = 0.0);
};



#endif //SHAPEFACTORY_H
