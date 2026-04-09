#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

// 모델 함수: y = a * exp(b * x)
double model(double x, double a, double b) {
    return a * std::exp(b * x);
}

// 잔차 계산
Eigen::VectorXd residuals(const std::vector<double>& x,
                          const std::vector<double>& y,
                          double a, double b) {
    Eigen::VectorXd r(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        r(i) = y[i] - model(x[i], a, b);
    }
    return r;
}

int main() {
    // 예제 데이터
    std::vector<double> x = {0, 1, 2, 3, 4};
    std::vector<double> y = {1.0, 2.7, 7.4, 20.1, 55.0};

    // 초기 추정값
    double a = 1.0;
    double b = 1.0;

    double learning_rate = 0.001;
    int iterations = 10000;

    for (int i = 0; i < iterations; ++i) {
        Eigen::VectorXd r = residuals(x, y, a, b);

        // 단순한 수치적 경사 하강법 (실제로는 LM 알고리즘을 쓰는 것이 더 안정적)
        double grad_a = 0.0;
        double grad_b = 0.0;
        for (size_t j = 0; j < x.size(); ++j) {
            grad_a += -2 * r(j) * std::exp(b * x[j]);
            grad_b += -2 * r(j) * a * x[j] * std::exp(b * x[j]);
        }

        a -= learning_rate * grad_a;
        b -= learning_rate * grad_b;
    }

    std::cout << "추정된 파라미터: a = " << a << ", b = " << b << std::endl;
    return 0;
}
