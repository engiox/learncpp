#include <iostream>
#include <chrono>

template <typename T>
class Auto_ptr3
{
    T* m_ptr;
public:
    Auto_ptr3(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr3() { delete m_ptr; }
    Auto_ptr3(const Auto_ptr3& a) {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr3& operator=(const Auto_ptr3& a) {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() const { return m_ptr == nullptr; }
};

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

Auto_ptr3<Resource> generateResource()
{
    Auto_ptr3<Resource> res{ new Resource };
    return res;
}

template <typename T>
class Auto_ptr4
{
    T* m_ptr;
public:
    Auto_ptr4(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr4() { delete m_ptr; }
    Auto_ptr4(const Auto_ptr4& a) {
        m_ptr = new T;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr4(Auto_ptr4&& a) noexcept : m_ptr{ a.m_ptr } {
        a.m_ptr = nullptr;
    }
    Auto_ptr4& operator=(const Auto_ptr4& a) {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        *m_ptr = *a.m_ptr;
    }
    Auto_ptr4& operator=(Auto_ptr4&& a) noexcept {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
        return *this;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isNull() { return this == nullptr; }
};

Auto_ptr4<Resource> generateResourceR()
{
    Auto_ptr4<Resource> res{ new Resource };
    return res;
}

template <typename T>
class Auto_ptr5
{
    T* m_ptr;
public:
    Auto_ptr5(T* ptr = nullptr) : m_ptr{ ptr } {}
    ~Auto_ptr5() { delete m_ptr; }
    Auto_ptr5(const Auto_ptr5& a) = delete;
    Auto_ptr5(Auto_ptr5& a) noexcept : m_ptr{ a.m_ptr } {
        a.m_ptr = nullptr;
    }
    Auto_ptr5& operator=(const Auto_ptr5& a) = delete;
    Auto_ptr5& operator=(Auto_ptr5& a) noexcept {
        if (&a == this)
            return *this;
        delete m_ptr;
        m_ptr = a.m_ptr;
        a.m_ptr = nullptr;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
    bool isBull() { return m_ptr == nullptr; }
};

template <typename T>
class DynamicArray
{
    T* m_array;
    int m_length;
public:
    DynamicArray(int len) : m_array{ new T[len] }, m_length{ len } {}
    ~DynamicArray() { delete[] m_array; }
    DynamicArray(const DynamicArray& dar) = delete;
//    DynamicArray(const DynamicArray& dar)
//        : m_array{ new T[dar.m_length] }, m_length{ dar.m_length }
//    {
//        for (int i{0}; i < m_length; ++i) {
//            m_array[i] = dar.m_array[i];
//        }
//    }
    DynamicArray& operator=(const DynamicArray& dar) = delete;
//    DynamicArray& operator=(const DynamicArray& dar) {
//        if (&dar == this) return *this;
//        delete[] m_array;
//        m_length = dar.m_length;
//        m_array = new T[m_length];
//        for (int i{0}; i < m_length; ++i) {
//            m_array[i] = dar.m_array[i];
//        }
//        return *this;
//    }
    DynamicArray(DynamicArray&& arr) noexcept 
        : m_array{ arr.m_array }, m_length{ arr.m_length } {
        arr.m_array = nullptr;
        arr.m_length = 0;
        std::cout << "Move constructor executed\n";
    }
    DynamicArray& operator=(DynamicArray&& arr) noexcept {
        if (&arr == this) return *this;
        delete[] m_array;
        m_array = arr.m_array;
        m_length = arr.m_length;
        arr.m_array = nullptr;
        arr.m_length = 0;
        std::cout << "Move assignment executed\n";
        return *this;
    }
    int getLength() const { return m_length; }
    T& operator[](int idx) { return m_array[idx]; }
    const T& operator[](int idx) const { return m_array[idx]; }
};

class Timer
{
    using Clock = std::chrono::high_resolution_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;
    std::chrono::time_point<Clock> m_beg{ Clock::now() };
public:
    void reset() {
        m_beg = Clock::now();
    }
    double elapsed() const {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};

DynamicArray<int> cloneArrayAndDouble(const DynamicArray<int>& arr)
{
    DynamicArray<int> dbl{ arr.getLength() };
    for (int i{0}; i < arr.getLength(); ++i) {
        dbl[i] = arr[i] * 2;
    }
    return dbl;
}

int main()
{
//    Auto_ptr3<Resource> mainres;
//    std::cout << "Auto_ptr3 created\n";
//    mainres = generateResource();
//    std::cout << "Auto_ptr3 copy-assigned\n";
//    std::cout << '\n';
//    Auto_ptr4<Resource> mainresR;
//    std::cout << "Auto_ptr4 created\n";
//    mainresR = generateResourceR();
//    std::cout << "Auto_ptr4 copy-assigned\n";
//    std::cout << "finishing\n\n";

    Timer t;
    DynamicArray<int> arr(1000000);
    for (int i = 0; i < arr.getLength(); ++i) {
        arr[i] = i;
    }
    arr = cloneArrayAndDouble(arr);

    std::cout << t.elapsed();

    return 0;
}
