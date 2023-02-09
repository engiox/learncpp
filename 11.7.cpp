#include <cstring>
#include <iostream>
#include <string_view>

int main()
{
  std::string_view str{ "balloon" };

  std::cout << str << " has " << std::strlen(str.data()) << " letter(s)\n";
  std::cout << "str is " << str << '\n';
  std::cout << "str.data() is " << str.data() << '\n';
  std::cout << '\n';

  // remove the "b"
  str.remove_prefix(1);
  std::cout << str << " has " << std::strlen(str.data()) << " letter(s)\n";
  std::cout << "str is " << str << '\n';
  std::cout << "str.data() is " << str.data() << '\n';
  std::cout << '\n';
  // remove the "oon"
  str.remove_suffix(3);
  // Remember that the above doesn't modify the string, it only changes
  // the region that str is observing.

  std::cout << str << " has " << std::strlen(str.data()) << " letter(s)\n";
  std::cout << "str is " << str << '\n';
  std::cout << "str.data() is " << str.data() << '\n';


  
  std::string s{ "hello" };
  std::string_view v{ "world" };
  
  // Doesn't work
//  std::cout << (s + v) << '\n';
//  std::cout << (v + s) << '\n';
  
  // Potentially unsafe, or not what we want, because we're treating
  // the std::string_view as a C-style string.
  std::cout << (s + v.data()) << '\n';
  std::cout << (v.data() + s) << '\n';
  
  // Ok, but ugly and wasteful because we have to construct a new std::string.
  std::cout << (s + std::string{ v }) << '\n';
  std::cout << (std::string{ v } + s) << '\n';
  std::cout << (s + static_cast<std::string>(v)) << '\n';
  std::cout << (static_cast<std::string>(v) + s) << '\n';

  return 0;
}
