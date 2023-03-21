#include <iostream>
#include <ostream>
#include <string>
#include <string_view>

class MyString
{
    std::string m_str{};
public:
    MyString(const std::string& str = {}) : m_str{ str } {}
    friend std::ostream& operator<<(std::ostream& out, const MyString& mstr) {
        out << mstr.m_str;
        return out;
    }
    std::string operator()(size_t start, size_t len) {
        return m_str.substr(start, len);
    }
    std::string_view substr(size_t start, size_t len) {
//        return std::string_view{ m_str.substr(start, len) };  // WHY NOT WORKING ???
        return std::string_view{ m_str }.substr(start, len);
    }
};

int main()
{
    MyString s { "Hello, world!" };
    std::cout << s(7, 5) << '\n'; // start at index 7 and return 5 characters
    std::cout << s.substr(3, 8) << '\n';

    return 0;
}
