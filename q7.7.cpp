#include <iostream>

void first()
{
    char ch { 'a' };

    while (ch <= 'z') {
        std::cout << ch << ' ' << static_cast<int>(ch) << '\n';
        ++ch;
    }
}

void second()
{
    int outer {5};
    while (outer > 0) {
        int inner {outer};
        while (inner > 0) {
            std::cout << inner << ' ';
            --inner;
        }
        std::cout << '\n';
        --outer;
    }
}

void third()
{
    constexpr int max_range {5};
    int outer {1};
    while (outer <= max_range) {
        int inner {max_range};
        while (inner > 0) {
            if (inner <= outer) {
                std::cout << inner << ' ';
            }
            else {
                std::cout << "  ";
            }
            --inner;
        }
        std::cout << '\n';
        ++outer;
    }
}

int main()
{
    while (true) {
        std::cout << "Run Quiz 1~3 (q to quit): ";
        char choice {};
        std::cin >> choice;

        if (choice == 'q') {
            std::cout << "Quitting...\n";
            break;
        }
    
        switch (choice) {
            case '1':
                first();
                break;
            case '2':
                second();
                break;
            case '3':
                third();
                break;
            default:
                std::cout << "Wrong choice!\n";
        }
    }

    return 0;
}
