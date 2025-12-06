#include <iostream>
#include <vector>

class lectures {
    public:
    lectures(int a) {
        std::cout<<"Ctor"<<std::endl;
    };
    lectures(const lectures &other) {
        std::cout<<"Copy Ctor"<<std::endl;
    };
    lectures(lectures &&other) noexcept {
        std::cout<<"Move ctor"<<std::endl;
    };
};

struct TypeTest {
    explicit TypeTest(int x) {
        std::cout << "TypeTest(int)\n";
    }

    explicit TypeTest(double x) {
        std::cout << "TypeTest(double)\n";
    }
};

void type_deduction_demo() {
    std::cout << "\n===== TYPE DEDUCTION vs EMPLACE DEMO =====\n";

    std::vector<TypeTest> v;
    v.reserve(10);

    std::cout << "\n-- push_back with int --\n";
    v.push_back(TypeTest(10));
    // Geçici TypeTest(int) oluşturulur → sonra move

    std::cout << "\n-- emplace_back with int --\n";
    v.emplace_back(10);
    // Argüman doğrudan int → TypeTest(int)

    std::cout << "\n-- push_back with double --\n";
    v.push_back(TypeTest(3.14));
    // TypeTest(double) oluşturulur → sonra move

    std::cout << "\n-- emplace_back with double --\n";
    v.emplace_back(3.14);
    // Burada doğrudan double overload seçilir

    std::cout << "\n-- emplace_back with narrowing (char) --\n";
    char c = 65;
    v.emplace_back(c);
    // Burada char → int dönüşümü olur ama doğrudan ctor çağrılır

    // std::vector<TypeTest> v;
    // v.push_back(10);      // error
    // v.emplace_back(10);  // compilable

}

void comparison_demo() {
    std::vector<lectures> student;
    student.reserve(10);

    std::cout << "---- push_back with temporary ----\n";
    student.push_back(lectures(10));

    std::cout << "---- emplace_back with temporary ----\n";
    student.emplace_back(lectures(20));

    std::cout << "---- push_back with args ----\n";
    student.push_back(40);

    std::cout << "---- emplace_back with args ----\n";
    student.emplace_back(30);

    std::cout << "---- object initializers----\n";
    auto physics = lectures(10);

    auto math = lectures(20);

    std::cout << "---- push_back with named object ----\n";
    student.push_back(physics);

    std::cout << "---- emplace_back with named object ----\n";
    student.emplace_back(math);
};

int main() {

    //comparison_demo();
    type_deduction_demo();

    return 0;
}