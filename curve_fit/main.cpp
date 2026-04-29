
#include "curve_fit.h"
#include <iostream>

// 모델 함수: y = a * exp(-((x - b)^2) / (2 * c^2))
double gaussian(double x, const std::vector<double>& p) {
    return p[0] * std::exp(-std::pow((x - p[1]), 2) / (2.0 * std::pow(p[2], 2)));
}

int main() {
    // 샘플 데이터 생성
    std::vector<double> x = {-2.0, -1.0, 0.0, 1.0, 2.0, 3.0, 4.0};
    std::vector<double> y = {1.2, 3.5, 9.8, 8.1, 3.2, 0.9, 0.3};

    std::vector<double> pd = {14.3, 1.34, 4.23};
    std::cout << "Experimental parameters (a, b, c):\n";
    for (double p : pd) std::cout << p << " ";
    std::cout << std::endl;

    for (int i = 0; i < x.size(); ++i) {
        y[i] = gaussian(x[i], pd);
    }

    // 초기값 [a, b, c]
    std::vector<double> p0 = {10.0, 0.5, 1.0};

    try {
        auto [popt, pcov] = curve_fit(gaussian, x, y, p0);

        std::cout << "Fitted parameters (a, b, c):\n";
        for (double p : popt) std::cout << p << " ";
        std::cout << "\n\nCovariance matrix:\n" << pcov << "\n";
        
        std::cout << "\nParameter errors (sqrt(diag)): ";
        for (int i = 0; i < popt.size(); ++i)
            std::cout << std::sqrt(pcov(i, i)) << " ";
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
