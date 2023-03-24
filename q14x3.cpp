#include <iostream>
#include <ostream>
#include <cassert>

class IntArray
{
    int* m_piArray{nullptr};
    int  m_iLength{0};

    void deepDupe(IntArray& tgt, const IntArray& src)
    {
        tgt.m_iLength = src.m_iLength;

        if (tgt.m_piArray) delete[] tgt.m_piArray;

        tgt.m_piArray = new int[static_cast<size_t>(tgt.m_iLength)];

        for (int i{0}; i < src.m_iLength; ++i) {
            tgt.m_piArray[i] = src.m_piArray[i];
        }
    }

public:
    explicit IntArray(int length) : m_iLength{ length }
    {
        assert( length > 0 && "Array has no element!\n" );
        m_piArray = new int[static_cast<size_t>(m_iLength)]{};
    }

    IntArray(const IntArray& src) : m_iLength{ src.m_iLength }
    {
        deepDupe(*this, src);
    }

    ~IntArray()
    {
        delete[] m_piArray;
    }

    IntArray& operator=(const IntArray& src)
    {
        if (this != &src) deepDupe(*this, src);

        return *this;
    }

    int& operator[](const int index)
    {
        assert( index >= 0 && "Negative index!\n" );
        assert( index < m_iLength && "Out of range!\n");
        return m_piArray[index];
    }

    friend std::ostream& operator<<(std::ostream& out, const IntArray& iArr)
    {
        for (int i{0}; i < iArr.m_iLength; ++i) {
            out << iArr.m_piArray[i] << ' ';
        }
        return out;
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

void test()
{
}

int main()
{
    test();

	IntArray a{ fillArray() };
	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	std::cout << b << '\n';

	return 0;
}
