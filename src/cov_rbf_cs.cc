/**************************************************************
 libgp - Gaussian process library for Machine Learning
 Copyright (C) 2011 Universität Freiburg
 Author: Manuel Blum
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 ***************************************************************/

#include "cov_rbf_cs.h"
#include <cmath>

namespace libgp
{
  
  CovRBFCS::CovRBFCS() {}
  
  CovRBFCS::~CovRBFCS() {}
  
  bool CovRBFCS::init(int n)
  {
    input_dim = n;
    param_dim = 2;
    loghyper.resize(param_dim);
    loghyper.setZero();
    nu = input_dim - input_dim%2 + 1;
    threshold = INFINITY;
    return true;
  }
  
  inline double CovRBFCS::get(const Eigen::VectorXd &x1, const Eigen::VectorXd &x2)
  {
    double nrm = (x1-x2).norm();
    if (nrm > threshold) return 0.0;    
    double q = std::max(0.0, pow(1 - nrm/threshold, nu));
    double z = nrm/ell;
    return q*sf2*exp(-0.5*z*z);
  }

  /** @todo implement this */
  void CovRBFCS::grad(const Eigen::VectorXd &x1, const Eigen::VectorXd &x2, Eigen::VectorXd &grad)
  {
    grad << 0.0, 0.0;
  }
  
  void CovRBFCS::set_loghyper(const Eigen::VectorXd &p)
  {
    CovarianceFunction::set_loghyper(p);
    ell = exp(loghyper(0));
    sf2 = exp(2*loghyper(1));
  }
  
  std::string CovRBFCS::to_string()
  {
    return "CovRBFCS";
  }
  
  double CovRBFCS::get_threshold()
  {
    return threshold;
  }
  
  void CovRBFCS::set_threshold(double threshold)
  {
    this->threshold = threshold;
  }
}