// libgp - Gaussian process library for Machine Learning
// Copyright (c) 2013, Manuel Blum <mblum@informatik.uni-freiburg.de>
// All rights reserved.

// Modified by Mohit Mehndiratta <mohit005@e.ntu.edu.sg> 2019

#include "gp_sparse.h"

namespace libgp {

    const double log2pi = log(2 * M_PI);

    SparseGaussianProcess::SparseGaussianProcess(size_t input_dim, std::string covf_def, size_t _max_points)
            : GaussianProcess(input_dim, covf_def) {
        max_points = _max_points;
    }

    SparseGaussianProcess::SparseGaussianProcess(const char *filename) : GaussianProcess(filename) {
        max_points = this->sampleset->size();
    }

    SparseGaussianProcess::SparseGaussianProcess(size_t _max_points, const GaussianProcess &gp) : GaussianProcess(gp) {
        max_points = _max_points;
    }

    SparseGaussianProcess::~SparseGaussianProcess() {}


    std::tuple<Eigen::MatrixXd, Eigen::MatrixXd, Eigen::MatrixXd>

    SparseGaussianProcess::compute_KmmKuuKmu(SampleSet * sampleset_m, SampleSet * sampleset_u)
    {
        size_t n = sampleset_m->size();
        size_t nu = sampleset_u->size();

        // compute kernel matrix (lower triangle)
        Eigen::MatrixXd Kmm(n, n);
        Kmm.setZero(n, n);
        Kmm = (L.topLeftCorner(sampleset->size(), sampleset->size())*L.topLeftCorner(sampleset->size(), sampleset->size()).transpose()).triangularView<Eigen::Lower>();

        // compute kernel matrix (lower triangle)
        Eigen::MatrixXd Kuu(nu, nu);
        Kuu.setZero(nu, nu);
        for(size_t i = 0; i < nu; ++i) {
            for(size_t j = 0; j <= i; ++j) {
                (Kuu)(i, j) = cf->get(sampleset_u->x(i), sampleset_u->x(j));
            }
        }

        // compute kernel matrix
        Eigen::MatrixXd Kmu(n, nu);
        Kmu.setZero(n, nu);
        for(size_t i = 0; i < n; ++i) {
            for(size_t j = 0; j < nu; ++j) {
                // TO BE: check if the values for noise covariance is coming up in the below evaluation
                (Kmu)(i, j) = cf->get(sampleset_m->x(i), sampleset_u->x(j));
            }
        }

        return std::make_tuple(Kmm, Kuu, Kmu);
    }


}