//
// Created by oguzh on 4.12.2025.
//

#include "ShapeFactory.h"

#include "Circle.h"
#include "Rectangle.h"


std::unordered_map<std::string, ShapeFactory::Creator> &ShapeFactory::registry() {
    static std::unordered_map<std::string, ShapeFactory::Creator> instance;
    return instance;
}

void ShapeFactory::registerType(const std::string &type, Creator creator) {
    registry()[type] = std::move(creator);
}


std::unique_ptr<Shape> ShapeFactory::create(const std::string &type, double a, double b) {
    auto it = registry().find(type);
    if (it != registry().end()) {
        return it->second(a, b);
    }
    return nullptr;
}
