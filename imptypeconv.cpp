#include <iostream>

void print(int x) // print now takes an int parameter
{
	std::cout << x;
}

int main()
{
	print(5.5); // warning: we're passing in a double value

	return 0;
}
