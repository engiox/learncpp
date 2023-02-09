#include <iostream>
#include <string_view>

int main()
{
    constexpr std::string_view names[]{ "Alex", "Betty", "Caroline", "Dave", "Emily" };
    constexpr int scores[]{ 84, 92, 76, 81, 56 };

    int maxScore{ 0 };

    for (int i{ 0 }; auto score : scores) {
        if (score > maxScore) {
            std::cout << names[i] << " beat the previous best score of " << maxScore
                      << " by " << score - maxScore << " points with " << scores[i] << "!\n";
            maxScore = score;
        }
        ++i;
    }
    
    std::cout << "The best score was " << maxScore << '\n';

    return 0;
}
