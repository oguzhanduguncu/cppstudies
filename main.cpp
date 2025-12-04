#include <iostream>
#include <vector>
#include <memory>
#include "ShapeFactory.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangular.h"

int main() {

    ShapeFactory::registerType("circle",
        [](double a, double) {
            return std::make_unique<Circle>(a);
        });

    ShapeFactory::registerType("rectangle",
        [](double a, double b) {
            return std::make_unique<Rectangle>(a, b);
        });

    ShapeFactory::registerType("triangular",
        [](double a, double b) {
            return std::make_unique<Triangular>(a, b);
        });

    std::vector<std::unique_ptr<Shape>> shapes;

    if (auto s = ShapeFactory::create("circle", 5))
        shapes.push_back(std::move(s));

    if (auto s = ShapeFactory::create("rectangle", 4, 6))
        shapes.push_back(std::move(s));

    if (auto s = ShapeFactory::create("circle", 3))
        shapes.push_back(std::move(s));

    if (auto s = ShapeFactory::create("triangular", 3))
        shapes.push_back(std::move(s));

    for (const auto& s : shapes) {
        std::cout << s->area() << std::endl;
        s->draw();
    }

    return 0;
}