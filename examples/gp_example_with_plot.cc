#include "gp.h"
#include "gp_utils.h"

#include <Eigen/Dense>
#include <iostream>
#include <Python.h>
#include "matplotlibcpp.h"


namespace plt = matplotlibcpp;

using namespace libgp;

int main()
{
    int n = 400, m = 100;
    double tss = 0.0;

    // Initialize Gaussian process for 2-D input using the squared exponential covariance function with additive white noise.
    GaussianProcess gp(2, "CovSum (CovSEiso, CovNoise)");

    // Initialize hyperparameter vector
    Eigen::VectorXd params(gp.covf().get_param_dim());
    params << 0.0, 0.0, -2.0;

    // Set parameters of the covariance function
    gp.covf().set_loghyper(params);

    // Add training patterns
    for (int i = 0; i < n; ++i)
    {
        double x[] = {drand48() * 4 - 2, drand48() * 4 - 2};
        double y = Utils::hill(x[0], x[1]) + Utils::randn() * 0.1;
        gp.add_pattern(x, y);
    }

    // Generate data for plotting the GP function and the hill function
    std::vector<double> gp_x, gp_y, hill_x, hill_y;
    for (double x = -2.0; x <= 2.0; x += 0.1)
    {
        for (double y = -2.0; y <= 2.0; y += 0.1)
        {
            double point[] = {x, y};
            gp_x.push_back(x);
            gp_y.push_back(gp.f(point)); // Evaluate the Gaussian process at the point (x, y)
            hill_x.push_back(x);
            hill_y.push_back(Utils::hill(x, y));
        }
    }

    // Total squared error
    for (int i = 0; i < m; ++i)
    {
        double x[] = {drand48() * 4 - 2, drand48() * 4 - 2};
        double f = gp.f(x);
        double y = Utils::hill(x[0], x[1]);
        double error = f - y;
        tss += error * error;
    }

    std::cout << "MSE = " << tss / m << std::endl;

    // Plot the GP function and the hill function
    plt::plot(gp_x, gp_y, "b.");
    plt::plot(hill_x, hill_y, "r-");
    plt::xlabel("x");
    plt::ylabel("f(x)");
    plt::title("Gaussian Process vs Hill Function");
    plt::show();

    return 0;
}