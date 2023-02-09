#include <iostream>

struct Advertise
{
    int numberOfAds {};
    double percentClicked {};
    double averageEarning {};
};

double calcEarning(const Advertise& ads)
{
    return (ads.averageEarning * ads.numberOfAds * ads.percentClicked);
}

Advertise getAdvertising()
{
    Advertise temp {};
    std::cout << "How many ads were shown today? ";
    std::cin >> temp.numberOfAds;
    std::cout << "What percentage of ads were clicked on by users? ";
    std::cin >> temp.percentClicked;
    std::cout << "What was the average earnings per click? ";
    std::cin >> temp.averageEarning;

    return temp;
}

void printAdvertising(const Advertise& ads)
{
    std::cout << "Number of ads shown : " << ads.numberOfAds << '\n'
              << "Clicked through rate : " << ads.percentClicked << '\n'
              << "Average earnings per click : " << ads.averageEarning << '\n';
    std::cout << "Total Earnings: $" << calcEarning(ads) << '\n';
}

int main()
{
    Advertise ad { getAdvertising() };
    printAdvertising( ad );

    return 0;
}
