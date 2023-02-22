#include <iostream>
#include <iomanip>
#include <vector>

void countDown(int count)
{
    std::cout << "push " << count << '\n';

    if (count > 1)
        countDown(count-1); // countDown() calls itself recursively
                            //
    std::cout << "pop " << count << '\n';
}

void newLine()
{
    std::cout << '\n';
}

int sumTo(int sumto)
{
    if (sumto <= 0) return 0;
    if (sumto == 1) return 1;

    return sumTo(sumto - 1) + sumto;
}

int fibonacci(int count)
{
    std::cout << '!';

    if (count == 0) return 0;
    if (count == 1) return 1;

    return fibonacci(count - 1) + fibonacci(count - 2);
}

int fibonacciN(unsigned int count)
{
    std::cout << '!';

    static std::vector fibResult{0, 1};

    if (count < fibResult.size())
        return fibResult.at(count);

    fibResult.push_back(fibonacciN(count - 1) + fibonacciN(count - 2));
    return fibResult.at(count);
}

int main()
{
    countDown(5);

    std::cout << "sumTo(5): " << sumTo(5) << '\n';

    for (auto i = 0; i < 13; ++i) 
        std::cout << "fibonacci(" << std::setw(2) << i << "): "
                  << std::setw(4) << fibonacci(i) << '\n';

    for (u_int i = 0; i < 13; ++i) 
        std::cout << "fibonacciN(" << std::setw(2) << i << "): "
                  << std::setw(4) << fibonacciN(i) << '\n';

    return 0;
}
