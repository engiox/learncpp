#include <iostream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

// 1. 모델 함수 정의: f(x) = a * exp(b * x)
double model_func(double x, const VectorXd& params) {
    double a = params(0);
    double b = params(1);
    return a * exp(b * x);
}

// 2. 모델 함수의 자코비안(Jacobian) 계산
// 파라미터 a와 b에 대한 편미분:
// df/da = exp(b * x)
// df/db = a * x * exp(b * x)
MatrixXd compute_jacobian(const VectorXd& x_data, const VectorXd& params) {
    int n = x_data.size();
    MatrixXd J(n, 2); // 파라미터가 2개(a, b)이므로 n x 2 행렬
    double a = params(0);
    double b = params(1);

    for (int i = 0; i < n; ++i) {
        double exp_bx = exp(b * x_data(i));
        J(i, 0) = exp_bx;               // df/da
        J(i, 1) = a * x_data(i) * exp_bx; // df/db
    }
    return J;
}

// 3. Curve Fitting 함수 (Levenberg-Marquardt 핵심 로직)
VectorXd curve_fit(const VectorXd& x_data, const VectorXd& y_data, VectorXd params) {
    int n = x_data.size();
    int m = params.size();
    double lambda = 0.01; // Damping factor (LM 알고리즘의 핵심)
    double tolerance = 1e-6;
    int max_iter = 100;

    for (int iter = 0; iter < max_iter; ++iter) {
        // 잔차(Residuals) 계산: r = y_observed - y_model
        VectorXd residuals(n);
        for (int i = 0; i < n; ++i) {
            residuals(i) = y_data(i) - model_func(x_data(i), params);
        }

        // 자코비안 계산
        MatrixXd J = compute_jacobian(x_data, params);

        // Gauss-Newton 방정식의 변형: (J^T * J + lambda * I) * delta = J^T * residuals
        MatrixXd JtJ = J.transpose() * J;
        VectorXd Jtr = J.transpose() * residuals;
        
        // LM 업데이트: (JtJ + lambda * diag(JtJ))를 사용하여 수렴 안정성 확보
        MatrixXd damping = MatrixXd::Zero(m, m);
        for(int i=0; i<m; ++i) damping(i, i) = lambda;

        // 시스템 방정식 풀기: (JtJ + damping) * delta = Jtr
        VectorXd delta = (JtJ + damping).ldlt().solve(Jtr);

        // 파라미터 업데이트
        VectorXd next_params = params + delta;

        // 새로운 파라미터에서의 오차 계산 (성능 개선 여부 확인)
        double current_error = residuals.squaredNorm();
        VectorXd next_residuals(n);
        for (int i = 0; i < n; ++i) {
            next_residuals(i) = y_data(i) - model_func(x_data(i), next_params);
        }
        double next_error = next_residuals.squaredNorm();

        if (next_error < current_error) {
            // 오차가 줄어들면 lambda를 감소시키고 파라미터 확정
            lambda /= 10.0;
            params = next_params;
            if (delta.norm() < tolerance) break; // 충분히 수렴함
        } else {
            // 오차가 늘어나면 lambda를 증가시키고 다시 시도 (Gradient Descent 방향으로)
            lambda *= 10.0;
        }
    }
    return params;
}

int main() {
    // 1. 가상 데이터 생성 (실제 값: a=2.5, b=0.5)
    int n = 20;
    VectorXd x_data(n);
    VectorXd y_data(n);
    for (int i = 0; i < n; ++i) {
        x_data(i) = i * 0.5;
        y_data(i) = 2.5 * exp(0.5 * x_data(i)) + ((double)rand() / RAND_MAX - 0.5) * 0.5; // 노이즈 추가
    }

    // 2. 초기값 설정 (Initial Guess)
    VectorXd initial_params(2);
    initial_params << 1.0, 0.1;

    // 3. Curve Fitting 수행
    VectorXd optimized_params = curve_fit(x_data, y_data, initial_params);

    // 4. 결과 출력
    cout << "Optimized Parameters:" << endl;
    cout << "a = " << optimized_params(0) << " (Expected: 2.5)" << endl;
    cout << "b = " << optimized_params(1) << " (Expected: 0.5)" << endl;

    return 0;
}
