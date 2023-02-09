#include <iostream>

int main()
{
    std::cout << "Enter a integer: ";
    int smaller{};
    std::cin >> smaller;

    std::cout << "Enter a larger integer: ";
    int larger{};
    std::cin >> larger;

    if (smaller > larger) {
        int swap{ smaller };
        smaller = larger;
        larger = swap;
        std::cout << "Swapping the values\n";
    }

    std::cout << "The smaller value is " << smaller << '\n';
    std::cout << "The larger value is " << larger << '\n';

    return 0;
}
