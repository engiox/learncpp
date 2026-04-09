#include <iostream>
#include <vector>
#include <cmath>
#include <functional>
#include <Eigen/Dense>
#include <Eigen/NonLinearOptimization>

using Vec = Eigen::VectorXd;
using Mat = Eigen::MatrixXd;
using Func = std::function<double(double, const Vec&)>;

// 수치 미분: 중심 차분
Vec compute_residual(const std::vector<double>& xdata,
                     const std::vector<double>& ydata,
                     const Vec& params,
                     const Func& f) {
    int n = xdata.size();
    Vec r(n);
    for (int i = 0; i < n; ++i)
        r[i] = f(xdata[i], params) - ydata[i];
    return r;
}

// Jacobian 수치 근사: df_i/dp_j ≈ (f(x_i, p + ε e_j) - f(x_i, p - ε e_j)) / (2ε)
Mat compute_jacobian(const std::vector<double>& xdata,
                     const Vec& params,
                     const Func& f,
                     double eps = 1e-8) {
    int n = xdata.size();
    int m = params.size();
    Mat J(n, m);

    for (int j = 0; j < m; ++j) {
        Vec p_plus = params, p_minus = params;
        p_plus[j] += eps;
        p_minus[j] -= eps;

        for (int i = 0; i < n; ++i) {
            double y_plus = f(xdata[i], p_plus);
            double y_minus = f(xdata[i], p_minus);
            J(i, j) = (y_plus - y_minus) / (2 * eps);
        }
    }
    return J;
}

// Levenberg-Marquardt (Eigen 제공)
struct LMFunctor {
    const std::vector<double>& xdata;
    const std::vector<double>& ydata;
    const Func& f;
    double eps;  // for numerical Jacobian

    LMFunctor(const std::vector<double>& x, const std::vector<double>& y,
              const Func& func, double e = 1e-8)
        : xdata(x), ydata(y), f(func), eps(e) {}

    int variables() const { return -1; }  // not used

    // fvec: residuals
    void operator()(const Vec& params, Vec& fvec) const {
        fvec = ::compute_residual(xdata, ydata, params, f);
    }

    // fjac: jacobian
    void df(const Vec& params, Mat& fjac) const {
        fjac = ::compute_jacobian(xdata, params, f, eps);
    }
};

// curve_fit 스타일 함수 (p0 = initial guess)
std::pair<Vec, Mat> curve_fit(const Func& f,
                              const std::vector<double>& xdata,
                              const std::vector<double>& ydata,
                              const std::vector<double>& p0,
                              double ftol = 1e-8,
                              double xtol = 1e-8,
                              int maxfev = 1000) {
    int n_params = p0.size();
    Vec params = Eigen::Map<const Vec>(p0.data(), n_params);
    LMFunctor functor(xdata, ydata, f);

    // Eigen의 LevenbergMarquardt 구현 사용
    Eigen::LevenbergMarquardt<LMFunctor> lm(functor);
    Eigen::LevenbergMarquardt<LMFunctor>::Outputs info = lm.minimize(params);

    if (info != Eigen::LevenbergMarquardt<LMFunctor>::Success) {
        std::cerr << "Warning: LM did not converge\n";
    }

    // Covariance matrix approximation: (J^T J)^{-1} * σ²
    // σ² = ||r||² / (n - m)
    Vec residual = functor.compute_residual(xdata, ydata, params);
    double sigma2 = residual.squaredNorm() / (xdata.size() - n_params);
    Mat J(xdata.size(), n_params);
    functor.df(params, J);
    Mat JtJ = J.transpose() * J;

    // Regularize for numerical stability
    Mat cov = JtJ.inverse() * sigma2;

    return {params, cov};
}

// 예제: 지수 감쇠 함수 y = A * exp(-k * x) + b
double exp_decay(double x, const Vec& p) {
    return p[0] * std::exp(-p[1] * x) + p[2];
}

int main() {
    // 테스트 데이터 (A=2.5, k=0.8, b=1.0)
    std::vector<double> xdata = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<double> ydata = {3.5, 2.7, 2.1, 1.7, 1.4, 1.2, 1.1};

    std::vector<double> p0 = {2.0, 0.5, 1.0};  // initial guess

    auto [popt, pcov] = curve_fit(exp_decay, xdata, ydata, p0);

    std::cout << "Fitted params: " << popt.transpose() << "\n";
    std::cout << "Covariance matrix:\n" << pcov << "\n";

    return 0;
}
```

---

## 🔧 빌드 방법 (CMake 기준)

```cmake
cmake_minimum_required(VERSION 3.10)
project(curve_fit)

set(CMAKE_CXX_STANDARD 17)

find_package(Eigen3 REQUIRED)

add_executable(curve_fit main.cpp)
target_link_libraries(curve_fit Eigen3::Eigen)
```

