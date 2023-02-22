#include <iostream>
#include <iomanip>
#include <vector>

int fact(int num)
{
    std::cout << '!';

    if (num == 0) return 1;

    return num * fact(num - 1);
}

int factN(int num)
{
    std::cout << '!';

    static std::vector factResult{ 1 };

    if (num < static_cast<int>(factResult.size()))
        return factResult.at(static_cast<size_t>(num));

    factResult.push_back(factN(num - 1) * num);

    return factResult.at(static_cast<size_t>(num));
}

int sumDigits(int val)
{
    std::cout << '!';

    //if ( (val/10) == 0 ) return val;
    if (val < 10) return val;

    return sumDigits(val / 10) + (val % 10);
}

void printBinary(int val)
{
    std::cout << '!';

    if (val < 2) {
        std::cout << (val % 2);
        return;
    }
    printBinary(val / 2);
    std::cout << (val % 2);
}

void printBinaryA(int val)
{
    if (val == 0) return;

    printBinaryA(val / 2);
    std::cout << val % 2;
}

void printBinaryU(u_int val)
{
    if (val == 0) return;

    printBinaryU(val / 2);
    std::cout << val % 2;
}

void printBinaryUA(unsigned int val)
{
    if (val > 1)
        printBinaryUA( val / 2);

    std::cout << val % 2;
}

int main()
{
//    std::cout << "fact(7): " << fact(7) << '\n';
    for (int idx = 0; idx <= 7; ++idx) {
        std::cout << "fact(" << idx << "): " << std::setw(4) << fact(idx) << '\n';
    }

//    std::cout << "factN(7): " << factN(7) << '\n';
    for (int idx = 0; idx <= 7; ++idx) {
        std::cout << "factN(" << idx << "): " << std::setw(4) << factN(idx) << '\n';
    }

    std::cout << "sumDigits(357): " << sumDigits(357) << '\n';
    std::cout << "sumDigits(93427): " << sumDigits(93427) << '\n';

    std::cout << "Enter an integer: ";
    int decNum{};
    std::cin >> decNum;

    printBinary(decNum);
    std::cout << '\n';

    printBinaryA(decNum);
    std::cout << '\n';

    printBinaryU(static_cast<u_int>(decNum));
    std::cout << '\n';

    printBinaryUA(static_cast<u_int>(decNum));
    std::cout << '\n';

    return 0;
}
