#include <iostream>

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double getDouble()
{
    while (true) {
        std::cout << "Enter a double value: ";
        double x{};
        std::cin >> x;

        if (std::cin) {
            ignoreLine();
            return x;
        }

        std::cin.clear();
        ignoreLine();
    }
}

char getOperator()
{
    while (true) {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char op{};
        std::cin >> op;
        ignoreLine();
    
        switch (op) {
            case '+':
            case '-':
            case '*':
            case '/':
                return op;
            default:
                std::cerr << "Oops, that input is invalid. Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    switch (operation)
    {
    case '+':
        std::cout << x << " + " << y << " is " << x + y << '\n';
        break;
    case '-':
        std::cout << x << " - " << y << " is " << x - y << '\n';
        break;
    case '*':
        std::cout << x << " * " << y << " is " << x * y << '\n';
        break;
    case '/':
        std::cout << x << " / " << y << " is " << x / y << '\n';
        break;
    default:
        std::cerr << "Something went wrong : printResult() got an invalid operator.\n";
    }
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    printResult(x, operation, y);

    return 0;
}
