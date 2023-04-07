#ifndef _INTARRAY_H_
#define _INTARRAY_H_

#include <cassert>

class IntArray
{
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;
    IntArray(int size);
    ~IntArray();
    void erase();
    int& operator[](int index);
    int getLength();
    void reallocate(int newSize);   // destroy existing elements
    void resize(int newSize);       // keep existing elements
    IntArray(const IntArray& src);
    IntArray& operator=(const IntArray& src);   // self-assignment check !!!
    void insertBefore(int value, int index);
    void remove(int index);
    void insertAtBeginning(int value);
    void insertAtEnd(int value);
};

#endif
