#include <iostream>
#include <cassert>
#include <cmath>

bool isPrime(int x)
{
//    assert( (x > 1) && "integer greater than 1 is required");
    if (x <= 1) {
        std::cout << "inter greater than 1 required\n";
        return false;
    }

    int maxTest{ static_cast<int>(std::sqrt(x)) };

    for (int i { 2 }; i <= maxTest; ++i) {
        if (!(x % i)) {
            std::cout << x << " is not a prime!\n";
            return false;
        }
    }
    std::cout << x << " is A prime!\n";
    return true;
}

int main()
{
	assert(!isPrime(0));
    assert(!isPrime(1));
    assert(isPrime(2));
    assert(isPrime(3));
    assert(!isPrime(4));
    assert(isPrime(5));
    assert(isPrime(7));
    assert(!isPrime(9));
    assert(isPrime(11));
    assert(isPrime(13));
    assert(!isPrime(15));
    assert(!isPrime(16));
    assert(isPrime(17));
    assert(isPrime(19));
    assert(isPrime(97));
    assert(!isPrime(99));
    assert(isPrime(13417));

	std::cout << "Success!\n";

    return 0;
}
