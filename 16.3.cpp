#include <functional> // std::reference_wrapper
#include <iostream>
#include <vector>
#include <string>

class Teacher
{
private:
  std::string m_name{};

public:
  Teacher(const std::string& name)
      : m_name{ name }
  {
  }

  const std::string& getName() const { return m_name; }
};

class Department
{
private:
  const Teacher& m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers

public:
  Department(const Teacher& teacher)
      : m_teacher{ teacher }
  {
  }
};

void p1()
{
  // Create a teacher outside the scope of the Department
  Teacher bob{ "Bob" }; // create a teacher

  {
    // Create a department and use the constructor parameter to pass
    // the teacher to it.
    Department department{ bob };

  } // department goes out of scope here and is destroyed

  // bob still exists here, but the department doesn't

  std::cout << bob.getName() << " still exists!\n";
}

void p2()
{
    std::string tom{ "Tom" };
    std::string berta{ "Berta" };

    std::vector<std::reference_wrapper<std::string>> names{ tom, berta }; // these strings are stored by reference, not value

    std::string jim{ "Jim" };

    names.push_back(jim);

    for (auto name : names) {
        // Use the get() member function to get the referenced string.
        name.get() += " Beam";
    }

    std::cout << jim << '\n'; // Jim Beam
}

int main()
{
    p1();
    p2();

    return 0;
}
