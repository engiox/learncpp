#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <numeric>
#include <Eigen/Dense>
#include <stdexcept>
#include <limits>

template<typename Func>
auto curve_fit(
    Func model,
    const std::vector<double>& xdata,
    const std::vector<double>& ydata,
    const std::vector<double>& p0,
    int max_iter = 100,
    double tol = 1e-6
) {
    if (xdata.size() != ydata.size() || xdata.empty())
        throw std::invalid_argument("xdata and ydata must be non-empty and same size.");
    if (p0.empty())
        throw std::invalid_argument("Initial guess p0 must not be empty.");

    int n = static_cast<int>(xdata.size());
    int m = static_cast<int>(p0.size());

    // ✅ 수정: const vector를 읽기 전용 Eigen 맵으로 연결
    const Eigen::Map<const Eigen::VectorXd> ydata_vec(ydata.data(), n);
    
    std::vector<double> p = p0;
    double lambda = 0.001;
    double prev_chi2 = 1e300;

    // 초기 모델 평가
    Eigen::VectorXd y_pred(n);
    for (int i = 0; i < n; ++i) y_pred[i] = model(xdata[i], p);
    Eigen::VectorXd r = ydata_vec - y_pred;
    double chi2 = r.dot(r);

    for (int iter = 0; iter < max_iter; ++iter) {
        double rel_chi2_change = std::abs(prev_chi2 - chi2) / (std::abs(prev_chi2) + 1e-12);
        if (rel_chi2_change < tol) break;
        prev_chi2 = chi2;

        // 1. 수치적 Jacobian (Central Difference)
        Eigen::MatrixXd J(n, m);
        for (int j = 0; j < m; ++j) {
            double h = std::sqrt(std::numeric_limits<double>::epsilon()) * std::max(1.0, std::abs(p[j]));
            std::vector<double> p_plus = p, p_minus = p;
            p_plus[j] += h; p_minus[j] -= h;

            Eigen::VectorXd y_plus(n), y_minus(n);
            for (int i = 0; i < n; ++i) {
                y_plus[i] = model(xdata[i], p_plus);
                y_minus[i] = model(xdata[i], p_minus);
            }
            J.col(j) = (y_plus - y_minus) / (2.0 * h);
        }

        // 2. LM 업데이트
        Eigen::MatrixXd JtJ = J.transpose() * J;
        Eigen::VectorXd Jtr = J.transpose() * r;
        Eigen::MatrixXd D = JtJ;
        for (int i = 0; i < m; ++i) D(i, i) += lambda * JtJ(i, i);

        Eigen::VectorXd delta;
        try {
            delta = D.ldlt().solve(Jtr);
        } catch (...) {
            throw std::runtime_error("Normal matrix is singular or ill-conditioned.");
        }

        // 3. 파라미터 업데이트
        std::vector<double> p_new = p;
        for (int j = 0; j < m; ++j) p_new[j] += delta[j];

        Eigen::VectorXd y_pred_new(n);
        for (int i = 0; i < n; ++i) y_pred_new[i] = model(xdata[i], p_new);
        Eigen::VectorXd r_new = ydata_vec - y_pred_new;
        double chi2_new = r_new.dot(r_new);

        // 4. 수용/거절
        if (chi2_new < chi2) {
            p = p_new;
            chi2 = chi2_new;
            lambda *= 0.2;
        } else {
            lambda *= 5.0;
        }

        // ✅ std::vector norm 직접 계산 (inner_product 사용)
        double p_norm = std::sqrt(std::inner_product(p.begin(), p.end(), p.begin(), 0.0));
        if (delta.norm() / (p_norm + 1e-12) < tol) break;
    }

    // 5. 공분산 행렬 계산 (최종 Jacobian 재계산)
    Eigen::VectorXd y_pred_final(n);
    for (int i = 0; i < n; ++i) y_pred_final[i] = model(xdata[i], p);
    Eigen::VectorXd r_final = ydata_vec - y_pred_final;
    double dof = std::max(1.0, static_cast<double>(n) - m);
    double scale = r_final.dot(r_final) / dof;

    Eigen::MatrixXd J_final(n, m);
    for (int j = 0; j < m; ++j) {
        double h = std::sqrt(std::numeric_limits<double>::epsilon()) * std::max(1.0, std::abs(p[j]));
        std::vector<double> p_plus = p, p_minus = p;
        p_plus[j] += h; p_minus[j] -= h;
        Eigen::VectorXd y_plus(n), y_minus(n);
        for (int i = 0; i < n; ++i) {
            y_plus[i] = model(xdata[i], p_plus);
            y_minus[i] = model(xdata[i], p_minus);
        }
        J_final.col(j) = (y_plus - y_minus) / (2.0 * h);
    }

    Eigen::MatrixXd cov;
    try {
        cov = scale * (J_final.transpose() * J_final).inverse();
    } catch (...) {
        std::cerr << "Warning: Covariance matrix could not be computed (singular).\n";
        cov = Eigen::MatrixXd::Zero(m, m);
    }

    return std::make_pair(p, cov);
}
