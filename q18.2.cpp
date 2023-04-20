#include <iostream>
#include <string_view>

class A
{
public:
	A() { std::cout << getName(); } // note addition of constructor

	virtual std::string_view getName() const { return "A"; }
};

class B : public A
{
public:
	virtual std::string_view getName() const { return "B"; }
};

class C : public B
{
public:
	virtual std::string_view getName() const { return "C"; }
};

class D : public C
{
public:
	virtual std::string_view getName() const { return "D"; }
};

int main()
{
	C c {};

	return 0;
}
