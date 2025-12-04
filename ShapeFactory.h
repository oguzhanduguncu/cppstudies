//
// Created by oguzh on 4.12.2025.
//

#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include <functional>

#include "Shape.h"
#include <memory>
#include <string>
#include <unordered_map>

class ShapeFactory {
public:
    using Creator = std::function<std::unique_ptr<Shape>(double,double)>;

    static void registerType(const std::string& type, Creator creator);
    static std::unique_ptr<Shape> create(const std::string& type, double a, double b = 0.0);

private:
    static std::unordered_map<std::string,Creator>& registry();
};



#endif //SHAPEFACTORY_H
