// ==================== curve_fit.hpp ====================
#pragma once

#include <Eigen/Dense>
#include <vector>
#include <functional>
#include <cmath>
#include <stdexcept>
#include <iostream>

// ---------------------------------------------------------------------------
// Helper to convert std::vector<double> <-> Eigen types
// ---------------------------------------------------------------------------
inline Eigen::VectorXd asVector(const std::vector<double>& v)
{
    Eigen::VectorXd x(v.size());
    for (size_t i = 0; i < v.size(); ++i) x(i) = v[i];
    return x;
}
inline std::vector<double> toVector(const Eigen::VectorXd& x)
{
    std::vector<double> v(x.size());
    for (size_t i = 0; i < x.size(); ++i) v[i] = x(i);
    return v;
}

// ---------------------------------------------------------------------------
// The core LM routine
// ---------------------------------------------------------------------------
/**
 * @brief Fit a model to data using Levenberg–Marquardt.
 *
 * @tparam ModelFunc  Signature: f(params, x) -> y
 *        where `params` is a std::vector<double> (size = nParameters)
 *              `x` is a double (or any scalar type you pass) and
 *              the return type matches the y data (usually double).
 *
 * @param model   Callable that evaluates the model at a point.
 *                Example:   [](const std::vector<double>& p, double x){ return p[0]*std::exp(-p[1]*x); }
 * @param xData   Vector of independent variable values.
 * @param yData   Vector of dependent variable values (same length as xData).
 * @param p0      Initial guess for parameters (any size N).
 * @param maxIter Maximum number of LM iterations (default 200).
 * @param ftol    Minimum change in the cost function for convergence (default 1e-12).
 * @param gtol    Minimum change in gradient norm (default 1e-12).
 * @param ltol    Minimum change in λ (default 1e-12).
 * @param verbose If true prints iteration info.
 *
 * @return struct FitResult containing:
 *         - params: final parameters (vector<double>)
 *         - cost: final sum of squares
 *         - cov: estimated covariance matrix of the parameters (size N×N)
 *         - info: status string (e.g. "converged")
 *         - nIter: number of performed LM steps
 *
 * The covariance matrix is obtained as (JᵀJ)⁻¹ multiplied by the residual variance.
 * If the Jacobian is rank‑deficient the matrix will contain large values.
 */
template <typename ModelFunc>
struct FitResult {
    std::vector<double> params;   // best parameters
    double cost;                  // final sum of squares / residual norm²
    Eigen::MatrixXd cov;          // covariance matrix (N×N)
    std::string info;             // "converged", "maxIterReached", "rankDeficient", …
    int nIter;                    // number of LM steps
};

template <typename ModelFunc>
FitResult<ModelFunc> curve_fit(const ModelFunc& model,
                                 const std::vector<double>& xData,
                                 const std::vector<double>& yData,
                                 std::vector<double> p0,
                                 int maxIter = 200,
                                 double ftol = 1e-12,
                                 double gtol = 1e-12,
                                 double ltol = 1e-12,
                                 bool verbose = false)
{
    using Eigen::MatrixXd;
    using Eigen::VectorXd;
    using Eigen::Jacobian;

    // ---- sanity checks ----------------------------------------------------
    if (xData.size() != yData.size())
        throw std::invalid_argument("xData and yData must have the same length");
    const int n = static_cast<int>(xData.size());
    const int m = static_cast<int>(p0.size());
    if (m == 0) throw std::invalid_argument("Initial parameter vector must not be empty");

    // Convert data to Eigen for speed
    const VectorXd X = asVector(xData);
    const VectorXd Y = asVector(yData);

    // ---- allocate working arrays -------------------------------------------
    VectorXd p = asVector(p0);          // current parameters (size m)
    VectorXd pNew(m);                   // parameters after trial step
    VectorXd r = VectorXd::Zero(n);     // residuals
    VectorXd rOld = VectorXd::Zero(n);  // old residuals (used for ftol)

    // Jacobian: n rows, m columns. Eigen's autodiff is not used here – we provide it
    // via a callable supplied by the user (optional, but gives much better performance).
    // For simplicity we will compute J by finite differences.
    const double eps = 1e-8;   // FD step size

    MatrixXd J(n, m);
    double lambda = 1e-3;                // initial damping factor
    const double lambdaInit = lambda;    // remember for output

    // ---- cost function ------------------------------------------------------
    auto cost_func = [&](const VectorXd& theta) -> double {
        double sum = 0.0;
        for (int i = 0; i < n; ++i) {
            double yFit = model(toVector(theta), X(i));
            double diff = Y(i) - yFit;
            sum += diff * diff;
        }
        return sum;
    };
    double cost = cost_func(p);
    rOld = Y - Eigen::VectorXd::Zero(n);   // dummy init; will be overwritten below

    // ---- main LM loop --------------------------------------------------------
    bool converged = false;
    int nIter = 0;
    bool rankDeficient = false;

    for (int iter = 0; iter < maxIter; ++iter, ++nIter) {

        // 1) Compute residuals and Jacobian at current p
        for (int i = 0; i < n; ++i) {
            double yFit = model(toVector(p), X(i));
            r(i) = Y(i) - yFit;
        }

        // Compute Jacobian by finite differences
        for (int j = 0; j < m; ++j) {
            VectorXd pPert = p;
            pPert(j) += eps;
            for (int i = 0; i < n; ++i) {
                double yFitPert = model(toVector(pPert), X(i));
                J(i, j) = (yFitPert - (Y(i) - r(i))) / eps;   // (f(p+δj) - f(p))/δ
            }
        }

        // 2) Solve (JᵀJ + λI) Δ = Jᵀ r
        MatrixXd JTJ = J.transpose() * J;
        MatrixXd diag = MatrixXd::Identity(m, m) * lambda;
        MatrixXd A = JTJ + diag;                    // Levenberg matrix
        VectorXd b = J.transpose() * r;              // right‑hand side

        // Use Eigen's robust solve (QR). If A is singular we catch exception later.
        VectorXd delta;
        try {
            delta = A.colPivHouseholderQr().solve(b);
        } catch (const std::runtime_error& e) {
            rankDeficient = true;
            if (verbose) std::cerr << "LM: matrix became singular at iteration " << iter << "\n";
            break;
        }

        // 3) Evaluate trial cost
        pNew = p + delta;
        double costNew = cost_func(pNew);
        double costReduction = cost - costNew;

        // 4) Accept / reject step
        if (costReduction > 0) {
            // Accept
            p = pNew;
            cost = costNew;
            lambda = std::max(1.0e-12, lambda / 10.0);   // make it smaller
            if (verbose) std::cout << "Iter " << iter << ": cost=" << cost
                                   << "  λ=" << lambda << "  Δcost=" << costReduction << "\n";
        } else {
            // Reject – increase λ
            lambda *= 10.0;
            if (verbose) std::cout << "Iter " << iter << ": reject step, λ=" << lambda << "\n";
            // Do NOT update p, r, cost; just try again with larger λ
            --iter; // repeat this iteration
            continue;
        }

        // 5) Check convergence (both cost and parameter changes)
        VectorXd stepNorm = delta;   // just to have something
        double gradNorm = (J.transpose() * r).norm(); // gradient of the cost
        if (verbose) std::cout << "   gradNorm=" << gradNorm
                               << "  costChange=" << std::abs(costReduction) << "\n";

        if (std::abs(costReduction) < ftol ||
            stepNorm.norm() < gtol ||
            std::abs(gradNorm) < ltol) {
            converged = true;
            if (verbose) std::cout << "Converged after " << nIter << " iterations.\n";
            break;
        }

        // Keep residuals for next iteration (used only for gradient check)
        rOld = r;
    } // end LM loop

    // ---- post‑processing ----------------------------------------------------
    FitResult<ModelFunc> out;
    out.params = toVector(p);
    out.cost = cost;
    out.nIter = nIter;
    out.info = (converged ? "converged"
                          : (rankDeficient ? "rankDeficient"
                                           : "maxIterReached"));
    if (rankDeficient) {
        out.cov = Eigen::MatrixXd::Zero(m, m);
    } else {
        // Approximate covariance = (JᵀJ)⁻¹ * (cost / (n - m))
        MatrixXd JTJ = J.transpose() * J;
        MatrixXd JTJinv;
        try {
            JTJinv = JTJ.inverse();
        } catch (...) {
            JTJinv = MatrixXd::Zero(m, m);
        }
        double residualVar = (cost) / static_cast<double>(n - m);
        out.cov = JTJinv * residualVar;
    }

    return out;
}
