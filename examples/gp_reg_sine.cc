#include "gp.h"
#include "gp_utils.h"
#include "gp_sparse.h"
#include <Eigen/Dense>
#include <iostream>
#include "matplotlibcpp.h"
#include <vector>
#include <algorithm>
#include <cmath>

namespace plt = matplotlibcpp;
using namespace libgp;

int main()
{

    const int kNumTrainingPoints = 50;
    const int kNumTestPoints = 1;
    int n = 50, m = 100;
    double future_pred = 1.0;
    double tss = 0.0;

    GaussianProcess gp(2, "CovSum (CovSEiso, CovNoise)");
    Eigen::VectorXd params(gp.covf().get_param_dim());
    params << 0.0, 0.0, -2.0;
    gp.covf().set_loghyper(params);

   //SparseGP implementation

    gp.covf().set_loghyper(params);
    double training_points_mat[kNumTrainingPoints][2];
    double training_targets_vec[kNumTrainingPoints];
    double targets;


    // add training patterns





    // Create plotting data

    double step = 2 * M_PI / n;
    std::vector<double> sine_x, sine_y;
    for (int i = 0; i < n; ++i)
    {
        double x = i * step;
        double y = Utils::sinewave(x);
        gp.add_pattern(&x, y);
        sine_x.push_back(x);
        sine_y.push_back(Utils::sinewave(x));
    }


    //  // Create Sparse GP
    SparseGaussianProcess sgp(n, gp);
    sgp.sparsify();
    std::cout << "sgp sample size = " << sgp.get_sampleset_size() << "\n";


   //GP inference

    std::vector<double> gp_x, gp_y, gp_var, sgp_x, sgp_y, sgp_var;
    for (double x = 0.0; x <= 2 * M_PI + future_pred; x += 0.01)
    {
        double point[] = {x};
        gp_x.push_back(x);
        gp_y.push_back(gp.f(point));
        gp_var.push_back(gp.var(point));
        sgp_x.push_back(x);
        sgp_y.push_back(sgp.f(point));
        sgp_var.push_back(sgp.var(point));
    }

    for (int i = 0; i < m; ++i)
    {
        double x[] = {drand48() * 4 - 2, drand48() * 4 - 2};
        double f = gp.f(x);
        double y = Utils::sinewave(x[0]);
        double error = f - y;
        tss += error * error;
    }

    std::vector<double> std_dev;
    for (const auto& variance : gp_var) {
        double sd = std::sqrt(variance);
        std_dev.push_back(sd);
    }




    std::vector<double> gp_ub(gp_y.size()), gp_lb(gp_y.size());
    std::vector<double> sgp_ub(gp_y.size()), sgp_lb(gp_y.size());


    std::transform(gp_y.begin(), gp_y.end(), gp_var.begin(), gp_ub.begin(), std::plus<double>());
    std::transform(gp_y.begin(), gp_y.end(), gp_var.begin(), gp_lb.begin(), std::minus<double>());

    std::transform(sgp_y.begin(), sgp_y.end(), sgp_var.begin(), sgp_ub.begin(), std::plus<double>());
    std::transform(sgp_y.begin(), sgp_y.end(), sgp_var.begin(), sgp_lb.begin(), std::minus<double>());


    plt::named_plot("Dense GP", gp_x, gp_y, "b.");
    plt::named_plot("Sparse GP", sgp_x, sgp_y, "g.");

    plt::fill_between(gp_x, gp_lb, gp_ub, {{"color", "blue"}, {"alpha", "0.4"}});
    plt::named_plot("Data", sine_x, sine_y, "rx");
    plt::fill_between(sgp_x, sgp_lb, sgp_ub, {{"color", "green"}, {"alpha", "0.4"}});


    plt::xlabel("x");
    plt::ylabel("f(x)");
    plt::title("GPR Fitting of a Sine wave");
    plt::legend();
    plt::show();

    return 0;
}
