#include <iostream>
#include <string>

class Something
{
    int m_value{};
public:
    Something(int val = 0): m_value{ val } {}
    void setValue(int val)
    {
        m_value = val;
    }
    int getValue() const;
};

int Something::getValue() const
{
    return m_value;
}

void main1()
{
    const Something something{};

    const Something st{1};
//    something.m_value = 5;
//    something.setValue(5);

    std::cout << something.getValue();
}

class Date
{
private:
    int m_year {};
    int m_month {};
    int m_day {};

public:
    Date(int year, int month, int day)
    {
        setDate(year, month, day);
    }

    void setDate(int year, int month, int day)
    {
        m_year = year;
        m_month = month;
        m_day = day;
    }

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

void printDate(const Date &date)
{
    std::cout << date.getYear() << '/' << date.getMonth() << '/' << date.getDay() << '\n';
}

void main2()
{
    Date date{2016, 10, 16};
    printDate(date);
}

class Something3
{
    private:
        std::string m_value{};
        static int s_value;         // forward declaration : s_value{0}; --> ERROR

    public:
        Something3(const std::string &value=""): m_value{ value } {}
        std::string &getValue() { return m_value; }
        const std::string &getValue() const {return m_value;}
        int getSValue() const { return s_value; }
};

int Something3::s_value{0};         // actual Instantiation !!!

void main3()
{
	Something3 something;
	something.getValue() = "Hi"; // calls non-const getValue();
    std::cout << something.getValue() << '\n';

	const Something3 something2;
	something2.getValue(); // calls const getValue();

    std::cout << something2.getSValue() << '\n';
    Something3::s_value = 2;
    std::cout << something2.getSValue() << '\n';
}

int main()
{
    main1();
    main2();
    main3();

    return 0;
}
