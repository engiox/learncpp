#include <algorithm> // for std::max
#include <iostream>

class MyString
{
private:
	char* m_data {};
	int m_length {};

public:
	MyString(const char* data = nullptr, int length = 0 )
		: m_length { std::max(length, 0) }
	{
		if (length)
		{
			m_data = new char[static_cast<std::size_t>(length)];

			for (int i { 0 }; i < length; ++i)
				m_data[i] = data[i];
		}
	}
	~MyString()
	{
		delete[] m_data;
	}

	// Overloaded assignment
	MyString& operator= (const MyString& str);

	friend std::ostream& operator<<(std::ostream& out, const MyString& s);
};

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
	out << s.m_data;
	return out;
}

// A simplistic implementation of operator= (do not use)
MyString& MyString::operator= (const MyString& str)
{
	// if data exists in the current string, delete it
	if (m_data) delete[] m_data;

	m_length = str.m_length;
	m_data = nullptr;

	// copy the data from str to the implicit object
	if (m_length)
		m_data = new char[static_cast<std::size_t>(str.m_length)];

	for (int i { 0 }; i < str.m_length; ++i)
		m_data[i] = str.m_data[i];

	// return the existing object so we can chain this operator
	return *this;
}

int main()
{
	MyString alex("Alex", 5); // Meet Alex
	MyString employee;
	employee = alex; // Alex is our newest employee
	std::cout << employee; // Say your name, employee

	return 0;
}
