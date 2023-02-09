#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

struct Students {
    std::string firstName{};
    int grade{};
};

int getNumberOfStudents()
{
    int number{};
    do {
        std::cout << "How many students do you want to enter? ";
        std::cin >> number;
    } while (number <= 0);

    return number;
}

Students getStudent()
{
    Students stu{};
    std::cout << "Name: ";
    std::cin >> stu.firstName;
    std::cout << "Grade: ";
    std::cin >> stu.grade;

    return stu;
}

void printStudent(const Students &stu)
{
    std::cout << stu.firstName << " got a grade of " << stu.grade << '\n';
}

bool compareStudents(const Students &a, const Students &b)
{
    return (a.grade > b.grade);
}

int main()
{
    std::vector<Students> studs(static_cast<size_t>(getNumberOfStudents()));

    for (auto &idx : studs) {
        idx = getStudent();
    }

    std::sort(studs.begin(), studs.end(), compareStudents);

    for (auto idx : studs) {
        printStudent(idx);
    }

    return 0;
}
