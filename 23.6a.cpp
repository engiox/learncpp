#include <fstream>
#include <iostream>

int main()
{
    std::fstream outf;

    if (!outf) {
        std::cerr << "Sample 23.6 cannot be opened!\n";
        return 1;
    }

    outf.open("Sample23.6.txt", std::ios::out);

    outf << "This is line 1\n";
    outf << "This is line 2\n";

    return 0;
}
