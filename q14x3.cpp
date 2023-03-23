#include <iostream>
#include <ostream>
#include <cassert>

class IntArray
{
    int* m_pIA{ nullptr };
    size_t  m_size{ 0 };

public:
    IntArray(size_t sz) : m_size{ sz }
    {
        assert(sz > 0 && "Constructor with no element!\n");
        if (sz) {
            m_pIA = new int[static_cast<size_t>(sz)] {};
        }
    }

    IntArray(const IntArray& src) : m_size{ src.m_size }
    {
        if (this != &src) {
            delete[] m_pIA;

            m_pIA = new int[src.m_size]{};
            for (size_t idx{0}; idx < m_size; ++idx) {
                m_pIA[idx] = src.m_pIA[idx];
            }
        }
    }

    ~IntArray()
    {
        delete[] m_pIA;
    }

    int& operator[](const size_t idx)
    {
        assert( (idx < m_size) && "Index out of range!\n" );
        assert( m_pIA && "Indexing with nullpointer!\n" );
        return m_pIA[idx];
    }

    friend std::ostream& operator<<(std::ostream& ostr, const IntArray& iArr)
    {
        for (size_t sz{0}; sz < iArr.m_size; ++sz) {
            ostr << iArr.m_pIA[sz] << ' ';
        }
        return ostr;
    }
};

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };
    std::cout << "a @ " <<  &a << ": ";
	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

    std::cout << "b @ " <<  &b << ": ";
	std::cout << b << '\n';

	return 0;
}
