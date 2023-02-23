#include <iostream>
#include <cstdarg>
#include <string_view>
#include <typeinfo>

double findAverage(int count, ...)
{
    int sum{0};

    std::va_list nums;

    va_start(nums, count);              // va_start(list, args_before_...)
                                        // reset va_list to the FIRST param.

    for (int idx{0}; idx < count; ++idx) {
        sum += va_arg(nums, int);       // va_arg(list, type) MOVES va_list
                                        // to the NEXT paramter in Ellipsis!
    }

    va_end(nums);                       // va_end(lst) reset pointer to NULL

    return static_cast<double>(sum) / count;
}

double findAveDS(std::string_view decoder, ...)
{
    double sum{ 0 };

    std::va_list nums{};
    std::cout << "type of va_list: " << typeid(nums).name() << '\n';

    va_start(nums, decoder);
    std::cout << "type of string_view: " << typeid(decoder).name() << '\n';

    for (auto num_t : decoder) {
        std::cout << "type of t:decoder : " << typeid(num_t).name() << '\n';
        switch (num_t) {
            case 'i':
                sum += va_arg(nums, int);
                break;
            case 'd':
                sum += va_arg(nums, double);
                break;
            default:
                break;
        }
    }

    va_end(nums);

    return sum / std::size(decoder);
}

int main()
{
    std::cout << findAverage(6, 1, 2, 3, 4, 5, 6) << '\n';
    std::cout << findAveDS("iidiid", 1, 2, 3.0, 4, 5, 6.0) << '\n';

    return 0;
}
