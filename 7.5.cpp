#include <iostream>

void first()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }
}

void second()
{
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }
}

bool isVowel(char c)
{
    switch (c)
    {
        case 'a': // if c is 'a'
        case 'e': // or if c is 'e'
        case 'i': // or if c is 'i'
        case 'o': // or if c is 'o'
        case 'u': // or if c is 'u'
        case 'A': // or if c is 'A'
        case 'E': // or if c is 'E'
        case 'I': // or if c is 'I'
        case 'O': // or if c is 'O'
        case 'U': // or if c is 'U'
            return true;
        default:
            return false;
    }
}

void third()
{
    std::cout << "Enter a character: ";
    char ch {};
    std::cin >> ch;
    std::cout << (isVowel(ch) ? "Vowel\n" : "Consonant\n");
}

void fourth()
{
    std::cout << "Enter an integer: ";
    int num {};
    std::cin >> num;

    switch(num) {
        int a;
        case 1:
            int x;
            x = 1;
            std::cout << "int x;   x = 1;\n";
            std::cout << "x = " << x << '\n';
            break;
        case 2:
            std::cout << "x = " << x << '\n';
            break;
        default:
            std::cout << "default: int y {3};\n";
            int y {3};
            std::cout << "x = " << x << '\n';
            std::cout << "y = " << y << '\n';
            break;
    }
}

int main()
{
//    first();
//    second();
//    third();
    fourth();

    return 0;
}
