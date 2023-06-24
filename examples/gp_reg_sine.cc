#include "gp.h"
#include "gp_utils.h"
#include "gp_sparse.h"
#include <Eigen/Dense>
#include <iostream>
#include "matplotlibcpp.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include "rprop.h"
#include <fstream>

using namespace std;
namespace plt = matplotlibcpp;
using namespace libgp;

std::vector<std::vector<double>> calculate_force_estimates_and_obtain_data();
int main()
{
    std::vector<std::vector<double>> drone_data = calculate_force_estimates_and_obtain_data();
    // Extracting drone data

    std::vector<double> gt_x(drone_data[0].begin(), drone_data[0].end());
    std::vector<double> gt_y(drone_data[1].begin(), drone_data[1].end());
    std::vector<double> gp_pr_x1(drone_data[2].begin(), drone_data[2].end());
    std::vector<double> gp_pr_y(drone_data[3].begin(), drone_data[3].end());
    std::vector<double> pos_x_d(drone_data[4].begin(), drone_data[4].end());
    std::vector<double> vel_x_d(drone_data[5].begin(), drone_data[5].end());


    for (const auto& value : gt_x) {
        std::cout << value << "\n";
    }
    const int kNumTrainingPoints = 50;
    const int kNumTestPoints = 1;
    int n = 20, m = 100, n_int=1;
    double future_pred = 8.0;
    double tss = 0.0;

    GaussianProcess gp(2, "CovSum (CovSEiso, CovNoise)");
    GaussianProcess gp1(2, "CovSum (CovSEiso, CovNoise)");
    Eigen::VectorXd params(gp.covf().get_param_dim());
    params << 0.0, 0.0, -2.0;
    gp.covf().set_loghyper(params);




    // Adding training data
    double sine_mean;
    double step = 2 * M_PI / n;
    std::vector<double> sine_x, sine_y;
    std::vector<double> train_x, train_y;
    double y;
    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < n; ++i)
        {

            double x = (i + j)*step;
            if (j==0) {
                 y = Utils::sinewave(x,1,0);


            }
            if (j==1) {   //Add first sine wave to data
                x = x + n*step;
                y = Utils::sinewave((x),4, 1);
            }

            if (j==2) {  //Add second sine wave to data
                x = x + j*n*step;
                y = Utils::sinewave((x),1,0);
            }

           // if ( gp.get_sampleset_size()==n*20){  //remove data
           //     gp.remove_sample(1);
           //     train_x.erase(train_x.begin());
           //     train_y.erase(train_y.begin());

           // }
                gp.add_pattern(&x, y);
                sine_x.push_back(x);
                sine_y.push_back(y);
                train_x.push_back(x);
                train_y.push_back(y);

           // std::cout << "size data = " << sine_x.size() << "\n";
            //std::cout << "size data = " << y << "\n";
        }
    }

    //  // Create Sparse GP
    SparseGaussianProcess sgp(n/10, gp);
    sgp.sparsify();
    std::cout << "sgp sample size = " << sgp.get_sampleset_size() << "\n";
    std::cout << "gp input dimension = " << gp.get_sampleset_size() << "\n";


    //libgp::RProp rprop;
    //int num_it=50;
    //rprop.maximize(&gp, num_it, 0);
    //cout << "param_RProp = " << gp.covf().get_loghyper() << "\n";

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


    std::vector<double> std_dev;
    for (const auto& variance : gp_var) {
        double sd = std::sqrt(variance);
        std_dev.push_back(sd);
    }


    //Plotting



    std::vector<double> gp_ub(gp_y.size()), gp_lb(gp_y.size());
    std::vector<double> sgp_ub(gp_y.size()), sgp_lb(gp_y.size());


    std::transform(gp_y.begin(), gp_y.end(), gp_var.begin(), gp_ub.begin(), std::plus<double>());
    std::transform(gp_y.begin(), gp_y.end(), gp_var.begin(), gp_lb.begin(), std::minus<double>());

    std::transform(sgp_y.begin(), sgp_y.end(), sgp_var.begin(), sgp_ub.begin(), std::plus<double>());
    std::transform(sgp_y.begin(), sgp_y.end(), sgp_var.begin(), sgp_lb.begin(), std::minus<double>());


                    plt::named_plot("Dense GP", gp_x, gp_y, "b.");

    plt::fill_between(gp_x, gp_lb, gp_ub, {{"color", "blue"}, {"alpha", "0.4"}});
    plt::named_plot("Old Data", sine_x, sine_y, "rx");
    plt::named_plot("Training Data", train_x, train_y, "gx");



    std::vector<double> x_transition = {2 * M_PI, 2 * M_PI};  // Vertical line at x = 2.5
    std::vector<double> y_transition = {-1, 1}; // Range of y values for the line
    plt::plot(x_transition, y_transition);

    //plot sparse
    //plt::named_plot("Sparse GP", sgp_x, sgp_y, "g.");
    //plt::fill_between(sgp_x, sgp_lb, sgp_ub, {{"color", "green"}, {"alpha", "0.4"}});


    plt::xlabel("t");
    plt::ylabel("f(t)");
    plt::title("GPR Fitting of a Sine wave");
    plt::legend();
    plt::show();

    return 0;
}



std::vector<std::vector<double>> calculate_force_estimates_and_obtain_data() {
    std::string file_path = "home/hakim/Desktop/projects/GP_cpp/libgp/data/drone_data.txt";
    std::ifstream file(file_path);

    // Read the file
    std::vector<std::vector<double>> data;
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<double> columns;
        std::string column;
        while (std::getline(ss, column, ',')) {
            try {
                columns.push_back(std::stod(column));
            } catch (const std::invalid_argument& e) {
                // Skip the column if conversion fails
                continue;
            }
        }
        data.push_back(columns);
    }
    file.close();

    // Params
    const double g = 9.81;
    const double m = 3.0;

    // Extract the columns for plotting
    std::vector<double> time1;
    std::vector<double> pos_x;
    std::vector<double> pos_y;
    std::vector<double> pos_z;
    std::vector<double> vel_x;
    std::vector<double> vel_y;
    std::vector<double> vel_z;
    std::vector<double> roll;
    std::vector<double> pitch;
    std::vector<double> yaw;
    std::vector<double> thrust;
    std::vector<double> exec_time_1;
    std::vector<double> gp_pr_x;
    std::vector<double> gp_pr_y;
    std::vector<double> gp_pr_z;
    std::vector<double> p;
    std::vector<double> q;
    std::vector<double> r;
    std::vector<double> acc_x;
    std::vector<double> acc_y;
    std::vector<double> acc_z;
    std::vector<double> wind_x;
    std::vector<double> wind_y;
    std::vector<double> wind_z;

    for (const auto& row : data) {
        time1.push_back(row[0]);
        pos_x.push_back(row[4]);
        pos_y.push_back(row[5]);
        pos_z.push_back(row[6]);
        vel_x.push_back(row[7]);
        vel_y.push_back(row[8]);
        vel_z.push_back(row[9]);
        roll.push_back(row[20]);
        pitch.push_back(row[21]);
        yaw.push_back(row[22]);
        thrust.push_back(row[23]);
        exec_time_1.push_back(row[24]);
        gp_pr_x.push_back(row[29]);
        gp_pr_y.push_back(row[30]);
        gp_pr_z.push_back(row[31]);
        p.push_back(row[14]);
        q.push_back(row[15]);
        r.push_back(row[16]);
        acc_x.push_back(row[17]);
        acc_y.push_back(row[18]);
        acc_z.push_back(row[19]);
        wind_x.push_back(row[26]);
        wind_y.push_back(row[27]);
        wind_z.push_back(row[28]);
    }

    // Convert the extracted columns to doubles
    std::vector<double> gt_x;
    std::vector<double> gt_y;
    std::vector<double> gp_pr_x1;
    std::vector<double> pos_x_d;
    std::vector<double> vel_x_d;
    for (size_t i = 0; i < acc_x.size(); ++i) {
        gt_x.push_back(acc_x[i] - vel_y[i] * r[i] + q[i] * vel_z[i] - g * std::sin(pitch[i]));
    }
    for (size_t i = 0; i < acc_y.size(); ++i) {
        gt_y.push_back(acc_y[i] - vel_z[i] * p[i] + r[i] * vel_x[i] - g * std::sin(roll[i]) * std::cos(pitch[i]));
    }
    for (const auto& value : gp_pr_x) {
        gp_pr_x1.push_back(value);
    }
    for (const auto& value : pos_x) {
        pos_x_d.push_back(value);
    }
    for (const auto& value : vel_x) {
        vel_x_d.push_back(value);
    }

    return {gt_x, gt_y, gp_pr_x1, gp_pr_y, pos_x_d, vel_x_d};
}