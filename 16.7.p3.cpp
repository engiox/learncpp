#include <cassert> // for assert()
#include <initializer_list> // for std::initializer_list
#include <iostream>

class IntArray
{
private:
	int m_length{};
	int* m_data{};

public:
	IntArray() = default;

	IntArray(int length)
		: m_length{ length }
		, m_data{ new int[static_cast<size_t>(length)] {} }
	{
	}

	IntArray(std::initializer_list<int> list) // allow IntArray to be initialized via list initialization
		: IntArray(static_cast<int>(list.size())) // use delegating constructor to set up initial array
	{
		// Now initialize our array from the list
		int count{ 0 };
		for (auto element : list)
		{
			m_data[count] = element;
			++count;
		}
	}

	~IntArray()
	{
		delete[] m_data;
	}

//	IntArray(const IntArray&) = delete; // to avoid shallow copies
    IntArray(const IntArray& src) : m_length{ src.m_length }, m_data{ new int[m_length] }
    {
        for (int i{0}; i < m_length; ++i) {
            m_data[i] = src.m_data[i];
        }
    }
//	IntArray& operator=(const IntArray& list) = delete; // to avoid shallow copies
    IntArray& operator=(const IntArray& list)
    {
        delete[] m_data;
        m_length = list.m_length;
        m_data = new int[list.m_length];
        for (int i{0}; i < m_length; ++i) {
            m_data[i] = list.m_data[i];
        }
        return *this;
    }

	int& operator[](int index)
	{
		assert(index >= 0 && index < m_length);
		return m_data[index];
	}

	int getLength() const { return m_length; }
};

int main()
{
	IntArray array{};
	array = { 1, 3, 5, 7, 9, 11 }; // Here's our list assignment statement

	for (int count{ 0 }; count < array.getLength(); ++count)
		std::cout << array[count] << ' ';

	return 0;
}
