// lm_curve_fit.cpp
// Requires Eigen (https://eigen.tuxfamily.org/)
#include <Eigen/Dense>
#include <functional>
#include <vector>
#include <iostream>
#include <cmath>

using Vector = Eigen::VectorXd;
using Matrix = Eigen::MatrixXd;

// 타입: 모델 함수 f(x, params) -> double
using ModelFunc = std::function<double(double, const Vector&)>;

// Numerical Jacobian: compute J_ij = d f(x_i, p)/d p_j via forward differences
Matrix numerical_jacobian(const ModelFunc& f, const std::vector<double>& x,
                          const Vector& p, double eps = 1e-8) {
    int n = (int)x.size();
    int m = (int)p.size();
    Matrix J(n, m);
    Vector p_eps = p;
    for (int j = 0; j < m; ++j) {
        double delta = eps * std::max(1.0, std::abs(p[j]));
        p_eps = p;
        p_eps[j] += delta;
        for (int i = 0; i < n; ++i) {
            double f1 = f(x[i], p_eps);
            double f0 = f(x[i], p);
            J(i, j) = (f1 - f0) / delta;
        }
    }
    return J;
}

// Levenberg-Marquardt
struct FitResult {
    Vector params;
    Matrix cov; // covariance matrix (approx)
    double cost; // sum of squared residuals
    bool success;
};

FitResult curve_fit_lm(const ModelFunc& f,
                       const std::vector<double>& x,
                       const std::vector<double>& y,
                       const Vector& p0,
                       int maxiter = 100,
                       double ftol = 1e-8,
                       double xtol = 1e-8,
                       double gtol = 1e-8) {
    int n = (int)x.size();
    int m = (int)p0.size();
    Vector p = p0;
    double lambda = 1e-3;
    double v = 2.0;

    Vector residuals(n);
    for (int i = 0; i < n; ++i) residuals[i] = y[i] - f(x[i], p);
    double cost = residuals.squaredNorm() / 2.0;

    Matrix J = numerical_jacobian(f, x, p);
    Vector g = J.transpose() * residuals; // gradient approximation

    bool success = false;
    for (int iter = 0; iter < maxiter; ++iter) {
        // Check convergence: gradient
        if (g.norm() <= gtol) { success = true; break; }

        // Form normal equations: (J^T J + lambda * diag(J^T J)) dp = J^T r
        Matrix A = J.transpose() * J;
        Matrix diagA = A.diagonal().asDiagonal();
        Matrix lhs = A + lambda * diagA;
        Vector rhs = g;

        // solve for dp
        Eigen::ColPivHouseholderQR<Matrix> solver(lhs);
        Vector dp = solver.solve(rhs);

        if (dp.hasNaN()) break;

        if (dp.norm() <= xtol * (p.norm() + xtol)) { success = true; break; }

        Vector p_new = p + dp;
        // compute new residuals and cost
        Vector residuals_new(n);
        for (int i = 0; i < n; ++i) residuals_new[i] = y[i] - f(x[i], p_new);
        double cost_new = residuals_new.squaredNorm() / 2.0;

        double rho = (cost - cost_new) / (0.5 * dp.transpose() * (lambda * dp + rhs));
        if (rho > 0) {
            // accept
            p = p_new;
            cost = cost_new;
            J = numerical_jacobian(f, x, p);
            residuals = residuals_new;
            g = J.transpose() * residuals;
            lambda = lambda * std::max(1.0 / 3.0, 1.0 - std::pow(2.0 * rho - 1.0, 3));
            v = 2.0;
        } else {
            // reject
            lambda *= v;
            v *= 2.0;
        }

        if (std::abs(cost_new - cost) < ftol) { success = true; break; }
    }

    // Estimate covariance: cov = s_sq * inv(J^T J), where s_sq = 2*cost/(n-m)
    Matrix cov = Matrix::Zero(m, m);
    if (n > m) {
        Matrix JTJ = J.transpose() * J;
        Eigen::FullPivLU<Matrix> lu(JTJ);
        if (lu.isInvertible()) {
            double s_sq = (n > m) ? (2.0 * cost / (n - m)) : 0.0;
            cov = lu.inverse() * s_sq;
        } else {
            // fallback pseudo-inverse
            Matrix pinv = JTJ.completeOrthogonalDecomposition().pseudoInverse();
            double s_sq = (n > m) ? (2.0 * cost / (n - m)) : 0.0;
            cov = pinv * s_sq;
        }
    }

    FitResult res;
    res.params = p;
    res.cov = cov;
    res.cost = 2.0 * cost; // sum of squared residuals
    res.success = success;
    return res;
}

// Example usage
int main() {
    // Example model: a * exp(b * x) + c
    ModelFunc model = [](double x, const Vector& p) {
        return p[0] * std::exp(p[1] * x);
    };

    // synthetic data
    std::vector<double> x;
    std::vector<double> y;

    x = {0,1,2,3,4};
    y = {1,2.7,7.4,20.1,54.6};

    Vector p0(2);
    p0 << 1.0, 0.5;

    FitResult out = curve_fit_lm(model, x, y, p0);

    std::cout << "success: " << out.success << "\n";
    std::cout << "params:\n" << out.params << "\n";
    std::cout << "covariance:\n" << out.cov << "\n";
    std::cout << "ssr: " << out.cost << "\n";
    return 0;
}
