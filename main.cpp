#include <iostream>
#include <vector>
#include <memory>
#include "ShapeFactory.h"

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    if (auto s = ShapeFactory::create("circle", 5))
        shapes.push_back(std::move(s));

    if (auto s = ShapeFactory::create("rectangle", 4, 6))
        shapes.push_back(std::move(s));

    if (auto s = ShapeFactory::create("circle", 3))
        shapes.push_back(std::move(s));

    for (const auto& s : shapes) {
        std::cout << s->area() << std::endl;
        s->draw();
    }

    return 0;
}
