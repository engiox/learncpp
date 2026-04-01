#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <Eigen/Dense>

// curve_fit with LM algorithm
std::vector<double> curve_fit(
    std::function<double(double, const std::vector<double>&)> model,
    const std::vector<double>& xdata,
    const std::vector<double>& ydata,
    std::vector<double> p0,
    int max_iter = 100,
    double lambda = 1e-3)
{
    int n = xdata.size();
    int m = p0.size();
    Eigen::VectorXd params(m);
    for (int j = 0; j < m; j++) params[j] = p0[j];

    for (int iter = 0; iter < max_iter; iter++) {
        Eigen::VectorXd residual(n);
        Eigen::MatrixXd J(n, m);

        // residuals and Jacobian
        for (int i = 0; i < n; i++) {
            double y_pred = model(xdata[i], p0);
            residual[i] = ydata[i] - y_pred;

            for (int j = 0; j < m; j++) {
                std::vector<double> temp = p0;
                double eps = 1e-6;
                temp[j] += eps;
                double y_eps = model(xdata[i], temp);
                J(i, j) = (y_eps - y_pred) / eps;
            }
        }

        // LM update
        Eigen::MatrixXd A = J.transpose() * J + lambda * Eigen::MatrixXd::Identity(m, m);
        Eigen::VectorXd g = J.transpose() * residual;
        Eigen::VectorXd delta = A.ldlt().solve(g);

        // update parameters
        for (int j = 0; j < m; j++) {
            p0[j] += delta[j];
            params[j] = p0[j];
        }

        if (delta.norm() < 1e-8) break; // convergence check
    }

    std::vector<double> result(m);
    for (int j = 0; j < m; j++) result[j] = params[j];
    return result;
}

// Example model: y = a * exp(b * x)
double exp_model(double x, const std::vector<double>& p) {
    return p[0] * std::exp(p[1] * x);
}

int main() {
    std::vector<double> xdata = {0,1,2,3,4};
    std::vector<double> ydata = {1,2.7,7.4,20.1,54.6};

    std::vector<double> p0 = {1.0, 0.5}; // initial guess
    auto popt = curve_fit(exp_model, xdata, ydata, p0);

    std::cout << "Fitted parameters: ";
    for (auto v : popt) std::cout << v << " ";
    std::cout << std::endl;
}
