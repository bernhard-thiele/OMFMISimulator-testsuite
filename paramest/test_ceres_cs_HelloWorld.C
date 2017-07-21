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
#include "../../install/include/OMSimulator.h"

using ceres::NumericDiffCostFunction;
using ceres::CENTRAL;
using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;
using ceres::Solve;
using namespace std::chrono;

void* model; // global variable

// der(x) = a*x;
// x(0) = x_start;
struct OdeResidual {
  OdeResidual(double t, double x)
      : t_(t), x_(x) {}

  bool operator()(const double* const x_start,
                                        const double* const a,
                                        double* residual) const {
    oms_setReal(model, "HelloWorld.x_start", x_start[0]);
    oms_setReal(model, "HelloWorld.a", a[0]);
    oms_setStopTime(model, t_);
    oms_setTolerance(model, 1e-5);

    oms_initialize(model);
    oms_stepUntil(model, t_);

    double x = oms_getReal(model, "HelloWorld.x");
    oms_reset(model);

    residual[0] = x_ - x;
    return true;
  }

 private:
  const double t_;
  const double x_;
};

// der(x) = a*x;
// x(0) = x_start;
void the_reference_ode(double x_start, double a, double t, double* x){
  oms_setReal(model, "HelloWorld.x_start", x_start);
  oms_setReal(model, "HelloWorld.a", a);
  oms_setStopTime(model, t);
  oms_setTolerance(model, 1e-5);

  oms_initialize(model);
  oms_stepUntil(model, t);

  *x = oms_getReal(model, "HelloWorld.x");
  oms_reset(model);
}

int test_ceres_cs_HelloWorld() {
  google::InitGoogleLogging("test_ceres_cfunc_HelloWorld");
  model = oms_newModel();
  oms_setTempDirectory(".");
  oms_instantiateFMU(model, "../FMUs/cs_HelloWorld.fmu", "HelloWorld");
  //oms_describe(model);

  // compute the_reference
  constexpr double Ts = 0.1;
  constexpr double Tend = 1;
  constexpr int n = Tend / Ts + 1;
  double t[n];
  double x[n];
  double x_start_ref = 1;
  double a_ref = -1;
  std::cout << "i \t t \t x\n";
  t[0] = 0; x[0] = x_start_ref;
  std::cout << 0 << "\t" << t[0] << "\t" << x[0] << std::endl;
  for (int i=1; i <= n; ++i) {
    t[i] = t[i-1] + Ts;
    the_reference_ode(x_start_ref, a_ref, t[i], &x[i]);
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
  std::cout << "i \t t \t x\n";
  t_est[0] = 0; x_est[0] = x_start;
  std::cout << 0 << "\t" << t_est[0] << "\t" << x_est[0] << std::endl;
  for (int i=1; i <= n; ++i) {
    t_est[i] = t_est[i-1] + Ts;
    the_reference_ode(x_start, a, t_est[i], &x_est[i]);
    std::cout << i << "\t" << t_est[i] << "\t" << x_est[i] << std::endl;
  }
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

  oms_terminate(model);
  oms_unload(model);
  return 0;
}

/** main() only required if compiled to a standalone executable */
int main() {
  test_ceres_cs_HelloWorld();
  return 0;
}
