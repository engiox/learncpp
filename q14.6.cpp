#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

struct StudentGrade
{
    std::string name{};
    char grade{};
};

class GradeMap
{
    std::vector<StudentGrade> m_map{};
public:
    char& operator[](std::string_view stuName);
};

char& GradeMap::operator[](std::string_view stuName)
{
    auto found{ std::find_if(m_map.begin(), m_map.end(),
            [&](const auto& student){ return (student.name == stuName); })
            };
    if (found != m_map.end()) {
        return found->grade;
    }

    m_map.push_back({std::string{stuName}});
    return m_map.back().grade;
}

int main()
{
	GradeMap grades{};

	grades["Joe"] = 'A';
	grades["Frank"] = 'B';

	std::cout << "Joe has a grade of " << grades["Joe"] << '\n';
	std::cout << "Frank has a grade of " << grades["Frank"] << '\n';

	return 0;
}
