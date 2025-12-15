#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ranges>
#include <unordered_map>
#include <string>
#include <concepts>
#include <format>
#include <numeric>

struct Person {
    std::string name;
    int age;
    double salary;
};

std::vector<Person> people {
        {"Alice", 30, 5000},
        {"Bob", 22, 3000},
        {"Charlie", 40, 7000},
        {"Diana", 35, 6500},
        {"Eve", 28, 4000}
};

int main() {
    auto chosenppl =
        people |
            std::views::filter([](const Person& p) { return p.age > 25; })
            |
                std::views::transform([](const Person& p) { return p.name; })
            |
                std::views::take(2);
    std::ranges::for_each(chosenppl, [](const std::string& name) {
        std::cout << name << '\n';
    });

}
