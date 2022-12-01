#include <iostream>

int main()
{
    {
        using std::cout, std::endl;
        cout << "Hello world!" << endl;
    }
//    cout << "And you?\n";   // error: use of undeclared identifier 'cout'

    return 0;
}
