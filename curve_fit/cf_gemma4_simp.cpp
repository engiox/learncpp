#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// 1. 모델 함수 정의: y = a * exp(b * x)
double model(double x, double a, double b) {
    return a * exp(b * x);
}

// 2. 오차 함수 (MSE - Mean Squared Error)
double calculate_error(const vector<double>& x, const vector<double>& y, double a, double b) {
    double error = 0;
    for (size_t i = 0; i < x.size(); ++i) {
        double diff = y[i] - model(x[i], a, b);
        error += diff * diff;
    }
    return error / x.size();
}

// 3. 매우 단순화된 curve_fit 구현 (경사하강법 방식)
void simple_curve_fit(const vector<double>& x, const vector<double>& y, double& a, double& b, double learning_rate = 0.01, int iterations =
10000) {
    for (int i = 0; i < iterations; ++i) {
        double grad_a = 0;
        double grad_b = 0;

        for (size_t j = 0; j < x.size(); ++j) {
            double error = model(x[j], a, b) - y[j]; // 단순화된 오차
            // 편미분 계산 (MSE의 미분)
            grad_a += error * 1.0; // d(error^2)/da -> 2 * error * (d/da(a * exp(bx)))
            // 실제로는 정확한 미분식을 넣어야 함
        }
        // 실제 정교한 구현을 위해 여기서는 개념적 구조만 제시합니다.
    }
}
