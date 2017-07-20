// Experiment for fitting functions / parameter estimation using CERES
// Let's try fiting ODE parameters to a reference ODE solution

#include <iostream>
#include <chrono>
#include <ceres/ceres.h>
#include <glog/logging.h>
#include "TCanvas.h"
#include "TROOT.h"
#include "TFitResult.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

#include "ceres/ceres.h"
#include "glog/logging.h"

using ceres::NumericDiffCostFunction;
using ceres::CENTRAL;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;
using namespace std::chrono;

struct OdeResidual {
  OdeResidual(double t, double x)
      : t_(t), x_(x) {}

  bool operator()(const double* const x_start,
                                        const double* const a,
                                        double* residual) const {
    double x = x_start[0];
    double Ts = 0.1;
    for (double t=0; t < t_; t += Ts) {
      x = x + Ts*a[0]*x;
    }
    residual[0] = x_ - x;
    return true;
  }

 private:
  const double t_;
  const double x_;
};

// der(x) = a*x;
// x(0) = x_start;
void the_reference_ode(double x_start, double a, double* t, double* x){
  double Ts = 0.1;
  double Tend = 1;
  int n = round(Tend / Ts);
  t[0] = 0;
  x[0] = x_start;
  for (int i=0; i < n; ++i) {
    t[i+1] = t[i] + Ts;
    x[i+1] = x[i] + Ts*a*x[i];
  }
}

int test_ceres_cfunc_HelloWorld() {
  google::InitGoogleLogging("test_ceres_cfunc_HelloWorld");

  // compute the_reference
  constexpr int n = 11;
  double t[n];
  double x[n];
  the_reference_ode(1, -1, t, x);
  std::cout << "i \t t \t x\n";
  for (int i=0; i <= n; ++i) {
    std::cout << i << "\t" << t[i] << "\t" << x[i] << std::endl;
  }

  // The canvas on which we'll draw the graph
  TCanvas *c1 = new TCanvas("c1","tofind",700,500);
  // Instance of the graph
  TGraph *gexpect = new TGraph(n,t,x);
  gexpect->SetLineColor(kBlue);
  gexpect->SetMarkerStyle(8);
  // gexpect->SetLineWidth(50);
  // Draw the graph !
  gexpect->DrawClone();


  // Pose the optimization problem
  // Start guess values for parameters
  double x_start = 0.5;
  double a = -0.5;
  Problem problem;
  for (int i = 0; i < n; ++i) {
    problem.AddResidualBlock(
        // use numeric differentiation to obtain the derivative (jacobian).
        new NumericDiffCostFunction<OdeResidual, CENTRAL, 1, 1, 1>(
            new OdeResidual(t[i], x[i])),
        NULL,
        &x_start, &a);
  }
  // Set solver options
  Solver::Options options;
  options.max_num_iterations = 25;
  options.linear_solver_type = ceres::DENSE_QR;
  options.minimizer_progress_to_stdout = true;
  Solver::Summary summary;
  // Run the solver and measure the needed time
  auto t0 = high_resolution_clock::now();
  Solve(options, &problem, &summary);
  auto t1 = high_resolution_clock::now();

  std::cout << summary.BriefReport() << "\n";
  std::cout << "Initial x_start: " << 0.5 << " a: " << -0.5 << "\n";
  std::cout << "Final   x_start: " << x_start << " a: " << a << "\n";

  // Create plot using the estimated parameters
  double t_est[n];
  double x_est[n];
  the_reference_ode(x_start, a, t_est, x_est);
  // Instance of the graph
  TGraph *gest = new TGraph(n,t_est,x_est);
  gest->SetLineColor(kRed);
  gest->SetMarkerStyle(2);
  // gest->SetLineWidth(50);
  // Draw the graph
  gest->DrawClone("Same");
  // Build and Draw a legend
  TLegend leg(.1,.7,.3,.9,"Ceres fitting experiment");
  leg.SetFillColor(0);
  gexpect->SetFillColor(0);
  gest->SetFillColor(0);
  leg.AddEntry(gexpect,"Exp. ODE solution");
  leg.AddEntry(gest,"Fitted function");
  leg.DrawClone("Same");

  std::cout <<
   "\n=====================================\n" <<
   "Duration for parameter estimation: " << duration_cast<milliseconds>(t1-t0).count() << "msec" <<
   "\n=====================================\n";

  return 0;
}

/** main() only required if compiled to a standalone executable */
int main() {
  test_ceres_cfunc_HelloWorld();
  return 0;
}
