#include <iostream>
#include <string_view>

class A
{
public:
    virtual ~A() = default;
	virtual std::string_view getName1(int x) { return "A"; }
	virtual std::string_view getName2(int x) { return "A"; }
    virtual std::string_view getName3(int x) final { return "A"; }
};

class B : public A
{
public:
    ~B() = default;
	virtual std::string_view getName1(short int x) { return "B"; } // note: parameter is a short int
	virtual std::string_view getName2(int x) const { return "B"; } // note: function is const
    virtual std::string_view getName3(int x) { return "B"; }
};

int main()
{
	B b{};
	A& rBase{ b };
	std::cout << rBase.getName1(1) << '\n';
	std::cout << rBase.getName2(2) << '\n';

	return 0;
}
