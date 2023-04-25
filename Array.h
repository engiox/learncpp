#ifndef __ARRAY_H__
#define __ARRAY_H__

template <typename T>
class Array
{
    int m_length{};
    T* m_data{};

public:
    Array(int len);
    ~Array();
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;
    void erase();
    T& operator[](const int index) const;
    int getLength() const;
};

#include "Array.inl"

#endif
