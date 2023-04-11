#include <initializer_list> // for std::initializer_list
#include <iostream>

class Foo
{
public:
	Foo(int, int)
	{
		std::cout << "Foo(int, int)" << '\n';
	}

	// We've added a list constructor
	Foo(std::initializer_list<int> list) : Foo(list.size(), list.size())
	{
		std::cout << "Foo(std::initializer_list<int>)" << '\n';
	}

};

int main()
{
	// note that the following statement has not changed
	Foo f1{ 1, 2 }; // now calls Foo(std::initializer_list<int>)

	return 0;
}
