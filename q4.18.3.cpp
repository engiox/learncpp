#include <iostream>

double getValue();
char getChar();
void printCalc(double val1, double val2, char op);

double getValue()
{
    std::cout << "Enter a double value: ";
    double val{};
    std::cin >> val;
    return val;
}

void printCalc(double val1, double val2, char op)
{
    if (op == '+') {
       std::cout << val1 << " + " << val2 << " is " << val1 + val2;
       return;
    }
    if (op == '-') {
        std::cout << val1 << " - " << val2 << " is " << val1 - val2;
        return;
    }
    if (op == '*') {
        std::cout << val1 << " * " << val2 << " is " << val1 * val2;
        return;
    }
    if (op == '/') {
        if (val2 == 0) {
            std::cerr << "divided by zero!\n";
            return;
        }
        std::cout << val1 << " / " << val2 << " is " << val1 / val2;
        return;
    }
}

char getChar()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char op{};
    std::cin >> op;
    return op;
}

int main()
{
    double v1{getValue()};
    double v2{getValue()};
    char op{getChar()};

    printCalc(v1, v2, op);

    return 0;
}
