#pragma once
/**
 * curve_fit.hpp
 * Python scipy.optimize.curve_fit() C++ 구현
 * 알고리즘: Levenberg-Marquardt (비선형 최소제곱법)
 *
 * 사용법:
 *   auto result = curve_fit(func, x_data, y_data, p0);
 *   result.params   // 최적 파라미터
 *   result.covar    // 공분산 행렬
 *   result.success  // 수렴 여부
 */

#include <vector>
#include <functional>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <numeric>
#include <sstream>

namespace cf {

// ─── 간단한 행렬 (row-major) ────────────────────────────────────────────────
struct Matrix {
    int rows, cols;
    std::vector<double> data;

    Matrix(int r, int c, double val = 0.0)
        : rows(r), cols(c), data(r * c, val) {}

    double& operator()(int i, int j)       { return data[i * cols + j]; }
    double  operator()(int i, int j) const { return data[i * cols + j]; }

    // 전치
    Matrix T() const {
        Matrix R(cols, rows);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                R(j, i) = (*this)(i, j);
        return R;
    }

    // 행렬 곱
    Matrix operator*(const Matrix& B) const {
        if (cols != B.rows) throw std::runtime_error("Matrix size mismatch in multiply");
        Matrix R(rows, B.cols);
        for (int i = 0; i < rows; ++i)
            for (int k = 0; k < cols; ++k)
                for (int j = 0; j < B.cols; ++j)
                    R(i, j) += (*this)(i, k) * B(k, j);
        return R;
    }

    // 스칼라 곱
    Matrix operator*(double s) const {
        Matrix R = *this;
        for (auto& v : R.data) v *= s;
        return R;
    }

    // 덧셈
    Matrix operator+(const Matrix& B) const {
        Matrix R = *this;
        for (int i = 0; i < (int)R.data.size(); ++i) R.data[i] += B.data[i];
        return R;
    }
};

// ─── Cholesky 분해를 이용한 선형계 풀기: Ax = b ─────────────────────────────
// A는 대칭 양정치 행렬이어야 함
inline std::vector<double> solve_cholesky(const Matrix& A, const std::vector<double>& b) {
    int n = A.rows;
    std::vector<double> L(n * n, 0.0); // row-major
    auto Lrc = [&](int r, int c) -> double& { return L[r * n + c]; };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            double s = A(i, j);
            for (int k = 0; k < j; ++k) s -= Lrc(i, k) * Lrc(j, k);
            if (i == j) {
                if (s <= 0.0) throw std::runtime_error("Matrix is not positive definite (Cholesky failed)");
                Lrc(i, j) = std::sqrt(s);
            } else {
                Lrc(i, j) = s / Lrc(j, j);
            }
        }
    }

    // 전방 대입: Ly = b
    std::vector<double> y(n);
    for (int i = 0; i < n; ++i) {
        y[i] = b[i];
        for (int k = 0; k < i; ++k) y[i] -= Lrc(i, k) * y[k];
        y[i] /= Lrc(i, i);
    }

    // 후방 대입: L^T x = y
    std::vector<double> x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int k = i + 1; k < n; ++k) x[i] -= Lrc(k, i) * x[k];
        x[i] /= Lrc(i, i);
    }
    return x;
}

// ─── 행렬 역행렬 (Cholesky 이용) ────────────────────────────────────────────
inline Matrix invert_sym(const Matrix& A) {
    int n = A.rows;
    Matrix inv(n, n);
    std::vector<double> e(n, 0.0);
    for (int i = 0; i < n; ++i) {
        std::fill(e.begin(), e.end(), 0.0);
        e[i] = 1.0;
        auto col = solve_cholesky(A, e);
        for (int r = 0; r < n; ++r) inv(r, i) = col[r];
    }
    return inv;
}

// ─── 결과 구조체 ─────────────────────────────────────────────────────────────
struct CurveFitResult {
    std::vector<double> params;   // 최적 파라미터
    Matrix              covar;    // 공분산 행렬 (params.size × params.size)
    std::vector<double> std_err;  // 파라미터 표준 오차
    double              residual; // 최종 잔차 제곱합
    int                 iters;    // 반복 횟수
    bool                success;  // 수렴 성공 여부
    std::string         message;

    CurveFitResult(int n)
        : params(n), covar(n, n), std_err(n), residual(0), iters(0), success(false) {}
};

// ─── 옵션 구조체 ─────────────────────────────────────────────────────────────
struct CurveFitOptions {
    int    max_iter    = 1000;
    double ftol        = 1e-8;   // 함수값 상대 허용 오차
    double xtol        = 1e-8;   // 파라미터 상대 허용 오차
    double gtol        = 1e-8;   // 기울기 허용 오차
    double eps_jac     = 1e-7;   // 야코비안 수치 미분 보폭
    double lambda_init = 1e-3;   // LM 초기 damping factor
    double lambda_up   = 10.0;   // λ 증가 배율 (스텝 거부 시)
    double lambda_down = 0.1;    // λ 감소 배율 (스텝 수락 시)
    double lambda_max  = 1e16;
    double lambda_min  = 1e-16;
};

// ─── 핵심 함수 ───────────────────────────────────────────────────────────────
/**
 * @param func      f(x_scalar, params) → double  형태의 모델 함수
 * @param x_data    독립 변수 데이터
 * @param y_data    종속 변수 데이터
 * @param p0        초기 파라미터 추정값
 * @param opt       옵션 (생략 가능)
 */
inline CurveFitResult curve_fit(
    const std::function<double(double, const std::vector<double>&)>& func,
    const std::vector<double>& x_data,
    const std::vector<double>& y_data,
    std::vector<double> p0,
    const CurveFitOptions& opt = CurveFitOptions())
{
    const int N = (int)x_data.size(); // 데이터 포인트 수
    const int M = (int)p0.size();     // 파라미터 수
    if (N != (int)y_data.size()) throw std::runtime_error("x_data and y_data size mismatch");
    if (N < M) throw std::runtime_error("Not enough data points for the number of parameters");

    CurveFitResult res(M);
    std::vector<double> p = p0;

    // 잔차 벡터: r[i] = y_data[i] - f(x_data[i], p)
    auto compute_residuals = [&](const std::vector<double>& params) {
        std::vector<double> r(N);
        for (int i = 0; i < N; ++i)
            r[i] = y_data[i] - func(x_data[i], params);
        return r;
    };

    // 잔차 제곱합
    auto rss = [&](const std::vector<double>& r) {
        double s = 0.0;
        for (double v : r) s += v * v;
        return s;
    };

    // 야코비안 J[i][j] = ∂r[i]/∂p[j]  (수치 미분)
    auto compute_jacobian = [&](const std::vector<double>& params,
                                const std::vector<double>& r_cur) {
        Matrix J(N, M);
        for (int j = 0; j < M; ++j) {
            double h = opt.eps_jac * (std::abs(params[j]) + 1.0);
            std::vector<double> p_plus = params;
            p_plus[j] += h;
            std::vector<double> r_plus = compute_residuals(p_plus);
            for (int i = 0; i < N; ++i)
                J(i, j) = (r_plus[i] - r_cur[i]) / h;
        }
        return J;
    };

    double lambda = opt.lambda_init;
    std::vector<double> r = compute_residuals(p);
    double cost = rss(r);

    for (int iter = 0; iter < opt.max_iter; ++iter) {
        res.iters = iter + 1;

        Matrix J   = compute_jacobian(p, r);
        Matrix JtJ = J.T() * J;             // M×M

        // Jᵀr (M×1로 사용)
        std::vector<double> Jtr(M, 0.0);
        for (int j = 0; j < M; ++j)
            for (int i = 0; i < N; ++i)
                Jtr[j] += J(i, j) * r[i];

        // 기울기 수렴 체크
        double g_inf = *std::max_element(Jtr.begin(), Jtr.end(),
            [](double a, double b){ return std::abs(a) < std::abs(b); });
        if (std::abs(g_inf) < opt.gtol) {
            res.success = true;
            res.message = "Gradient convergence (gtol)";
            break;
        }

        // (JᵀJ + λI) Δp = Jᵀr
        Matrix A = JtJ;
        for (int j = 0; j < M; ++j) A(j, j) += lambda * A(j, j) + 1e-10;

        std::vector<double> dp;
        try {
            dp = solve_cholesky(A, Jtr);
        } catch (...) {
            // 수치 문제 → λ 키우고 재시도
            lambda = std::min(lambda * opt.lambda_up, opt.lambda_max);
            continue;
        }

        // 파라미터 업데이트 시도
        std::vector<double> p_new(M);
        for (int j = 0; j < M; ++j) p_new[j] = p[j] + dp[j];

        std::vector<double> r_new  = compute_residuals(p_new);
        double              cost_new = rss(r_new);

        // 이득비 ρ = (실제 감소) / (예측 감소)
        double pred_cost = 0.0;
        for (int j = 0; j < M; ++j)
            pred_cost += dp[j] * (lambda * dp[j] + Jtr[j]);

        double rho = (pred_cost > 0) ? (cost - cost_new) / pred_cost : -1.0;

        if (rho > 0) {
            // 스텝 수락
            double dp_norm = 0.0, p_norm = 0.0;
            for (int j = 0; j < M; ++j) {
                dp_norm += dp[j] * dp[j];
                p_norm  += p[j]  * p[j];
            }
            dp_norm = std::sqrt(dp_norm);
            p_norm  = std::sqrt(p_norm) + 1e-10;

            p    = p_new;
            r    = r_new;
            cost = cost_new;
            lambda = std::max(lambda * opt.lambda_down, opt.lambda_min);

            // 파라미터/함수값 수렴 체크
            if (dp_norm < opt.xtol * (p_norm + opt.xtol)) {
                res.success = true;
                res.message = "Parameter convergence (xtol)";
                break;
            }
            if (cost < opt.ftol * opt.ftol) {
                res.success = true;
                res.message = "Cost convergence (ftol)";
                break;
            }
        } else {
            // 스텝 거부 → λ 증가
            lambda = std::min(lambda * opt.lambda_up, opt.lambda_max);
            if (lambda >= opt.lambda_max) {
                res.message = "Lambda exceeded max (stalled)";
                break;
            }
        }
    }

    if (!res.success && res.message.empty())
        res.message = "Max iterations reached";

    // 최종 파라미터 저장
    res.params   = p;
    res.residual = cost;

    // 공분산 행렬: cov = σ² (JᵀJ)⁻¹,  σ² = RSS / (N - M)
    try {
        Matrix J_final = compute_jacobian(p, compute_residuals(p));
        Matrix JtJ_f   = J_final.T() * J_final;
        Matrix inv     = invert_sym(JtJ_f);
        double sigma2  = (N > M) ? cost / (N - M) : 1.0;
        res.covar = inv * sigma2;
        for (int j = 0; j < M; ++j)
            res.std_err[j] = std::sqrt(std::max(0.0, res.covar(j, j)));
    } catch (...) {
        // 역행렬 실패 → 공분산 infinite로 채움
        for (int j = 0; j < M; ++j)
            res.std_err[j] = std::numeric_limits<double>::infinity();
    }

    return res;
}

} // namespace cf


// ═══════════════════════════════════════════════════════════════════════════
//  사용 예시 (main 함수)
// ═══════════════════════════════════════════════════════════════════════════
/*
#include <iostream>
#include "curve_fit.hpp"

int main() {
    // 예시 1: 가우시안 피팅  f(x) = A * exp(-((x-mu)/sigma)^2 / 2)
    auto gaussian = [](double x, const std::vector<double>& p) {
        double A = p[0], mu = p[1], sigma = p[2];
        return A * std::exp(-std::pow((x - mu) / sigma, 2) / 2.0);
    };

    std::vector<double> x = {-3,-2,-1,0,1,2,3,4,5,6};
    std::vector<double> y = {0.02,0.11,0.37,0.91,1.65,2.18,2.12,1.53,0.79,0.29};
    std::vector<double> p0 = {2.0, 2.0, 2.0};  // 초기 추정

    auto res = cf::curve_fit(gaussian, x, y, p0);

    std::cout << "Success: " << res.success << " (" << res.message << ")\n";
    std::cout << "A     = " << res.params[0] << " ± " << res.std_err[0] << "\n";
    std::cout << "mu    = " << res.params[1] << " ± " << res.std_err[1] << "\n";
    std::cout << "sigma = " << res.params[2] << " ± " << res.std_err[2] << "\n";
    std::cout << "Residual RSS = " << res.residual << "\n";

    // 예시 2: 지수 감쇠  f(x) = A * exp(-b*x) + C
    auto exp_decay = [](double x, const std::vector<double>& p) {
        return p[0] * std::exp(-p[1] * x) + p[2];
    };

    // 예시 3: 사인 파형  f(x) = A * sin(ω*x + φ)
    auto sine_wave = [](double x, const std::vector<double>& p) {
        return p[0] * std::sin(p[1] * x + p[2]);
    };

    return 0;
}
*/
