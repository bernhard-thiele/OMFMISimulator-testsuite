// Experiment for fitting functions / parameter estimation
// Let's try fitting cs_fmu ODE parameters to a reference OMC ODE solution

// Most includes not necessary for Cling, but needed if file is compiled to standalone executable, e.g.,
// g++ -o test_cs_HelloWorld test_cs_HelloWorld.C `root-config --cflags --libs` -L../../3rdParty/FMIL/install/linux/lib/ -lfmilib_shared -L../../install/lib/ -lOMSimulatorLib

#include <iostream>
#include <chrono>

#include "TCanvas.h"
#include "TROOT.h"
#include "TFitResult.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

#include "../../install/include/OMSimulator.h"

using namespace std::chrono;

void* model; // global variable

// der(x) = p[1]*x;
// x(0) = p[0];
double the_ode(double* vars, double* pars) {
  // static int count = 0;
  // count++;
  // std::cout << "N" << count << std::endl;

  oms_setReal(model, "HelloWorld.x_start", pars[0]);
  oms_setReal(model, "HelloWorld.a", pars[1]);
  oms_setStopTime(model, vars[0]);
  oms_setTolerance(model, 1e-5);

  oms_initialize(model);
  oms_stepUntil(model, vars[0]);

  double x = oms_getReal(model, "HelloWorld.x");
  oms_reset(model);
  return x;
}

int test_cs_HelloWorld() {
  model = oms_newModel();
  oms_setTempDirectory(".");
  oms_instantiateFMU(model, "../FMUs/cs_HelloWorld.fmu", "HelloWorld");
  //oms_describe(model);

  TCanvas *c1 = new TCanvas("c1","tofind",700,500);

  TF1 fode1("ODE;time;Y Vals",the_ode,0,1,2);
  double x0=1; double a=-1;
  fode1.SetParameters(x0,a);
  fode1.SetParNames("x0","a");
  //fode1.DrawClone();
  TGraph *gexpect = new TGraph(&fode1);
  gexpect->SetLineColor(kBlue);
  gexpect->SetMarkerStyle(8);
  // gexpect->SetLineWidth(50);
  // Draw the graph !
  gexpect->DrawClone();


  // Create new function to perform fit
  TF1 fode2("fittet ODE par;time;Y Vals",the_ode,0,1,2);
  // "reset" parameters to start valued differing from reference
  fode2.SetParameters(0.5, -0.5);
  fode2.SetLineColor(kRed); fode2.SetLineStyle(2);
  // Fit it to the graph and measure the needed time
  auto t0 = high_resolution_clock::now();
  auto fitResPtr = gexpect->Fit(&fode2, "S");
  auto t1 = high_resolution_clock::now();

  // ... and retrieve fit results
  fitResPtr->Print(); // print fit results
  fode2.DrawClone("Same");

  // Build and Draw a legend
  TLegend leg(.1,.7,.3,.9,"My fitting experiment");
  leg.SetFillColor(0);
  gexpect->SetFillColor(0);
  leg.AddEntry(gexpect,"Exp. OM ODE solution");
  leg.AddEntry(&fode2,"Fitted OM ODE");
  leg.DrawClone("Same");

  std::cout <<
   "\n=====================================\n" <<
   "Duration for Fit(&fode2, \"S\"): " << duration_cast<milliseconds>(t1-t0).count() << "msec" <<
   "\n=====================================\n";

  oms_terminate(model);
  oms_unload(model);
  return 0;
}

/** main() only required if compiled to a standalone executable */
int main() {
  test_cs_HelloWorld();
  return 0;
}
