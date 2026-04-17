// ==================== main.cpp ====================
#include "curve_fit_nc2.hpp"
#include <iostream>

int main()
{
    // 1) Data – let's fit an exponential decay: y = a * exp(-b * x)
    std::vector<double> x = {0, 1, 2, 3, 4, 5};
    std::vector<double> y = {5.0, 3.2, 2.1, 1.4, 0.9, 0.6};   // noisy measurements

    // 2) Model function – must have signature (const std::vector<double>& p, double x)
    auto model = [](const std::vector<double>& p, double x) -> double {
        // p[0] = a , p[1] = b
        return p[0] * std::exp(-p[1] * x);
    };

    // 3) Initial guess (must be close enough!)
    std::vector<double> p0 = {4.0, 1.0};

    // 4) Run the fit
    auto result = curve_fit(model, x, y, p0, /*maxIter=*/500, /*verbose=*/true);

    // 5) Print results
    std::cout << "\n--- Fit result -------------------------------------------------\n";
    std::cout << "Status : " << result.info << "\n";
    std::cout << "Iterations : " << result.nIter << "\n";
    std::cout << "Final cost (sum of squares) : " << result.cost << "\n";

    std::cout << "\nEstimated parameters:\n";
    for (size_t i = 0; i < result.params.size(); ++i) {
        std::cout << "  p[" << i << "] = " << result.params[i] << "\n";
    }

    // Covariance matrix (2×2 in this case) – useful for error estimates
    Eigen::MatrixXd cov = result.cov;
    std::cout << "\nEstimated covariance matrix:\n" << cov << "\n";

    return 0;
}
