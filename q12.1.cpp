#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <typeinfo>
#include <cstring>
#include <functional>

template <typename T>
T getValue(const std::string_view tName)
{
    T val{};

    while (true) {
        std::cout << "Enter a " << tName << ": ";
        std::cin >> std::ws >> val;
        if (std::cin.fail()) {
            std::cout << "Invalid input value! " << tName << " type is expeced!\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if ( (strchr(typeid(val).name(), 'c') != nullptr) &&
             (val != '+' && val != '-' && val!= '*' && val!= '/')
           ) {
            std::cout << "Not an operator!\n";
            continue;
        }
        return val;
    }
}

int add(int a, int b) { return a + b; }
int substract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return a / b; }

using ArithmeticFunction = std::function<int(int, int)>;

ArithmeticFunction getArithmeticFunction(char op)
{
    switch (op) {
        case '+': return add;
        case '-': return substract;
        case '*': return multiply;
        case '/': return divide;
        default:  return nullptr;
    }
}

int main()
{
    int  v1{getValue<int>("integer")}, v2{getValue<int>("integer")};
    char op{getValue<char>("operator")};

    std::cout << v1 << ' ' << op << ' ' << v2 << " = "
              << getArithmeticFunction(op)(v1, v2) << '\n';
//               ArithmeticFunction fcn{ getArithmeticFunction(op) };   fcn(v1, v2);

    return 0;
}
