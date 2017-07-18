// Experiment for fitting functions / parameter estimation
// Let's try fitting cs_fmu ODE parameters to a reference OMC ODE solution

#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <sstream>
#include <unistd.h>

#include "../../install/include/OMSimulator.h"

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}

// der(x) = p[1]*x;
// x(0) = p[0];
double the_ode(double* vars, double* pars) {
  // const char* version = oms_getVersion();
  // std::cout << version << std::endl;
  void* model = oms_newModel();
  oms_setTempDirectory(".");

  oms_instantiateFMU(model, "models/cs_HelloWorld.fmu", "HelloWorld");
  //oms_describe(model);

  oms_setReal(model, "HelloWorld.x_start", pars[0]);
  oms_setReal(model, "HelloWorld.a", pars[1]);
  oms_setStopTime(model, vars[0]);
  oms_setTolerance(model, 1e-5);

  // oms_simulate(model); // get segmentation violation

  oms_initialize(model);
  oms_stepUntil(model, vars[0]);

  // double tcur;
  // oms_getCurrentTime(model, &tcur);
  // while (tcur < vars[0]) {
  //   oms_doSteps(model, 0.1);
  //   oms_getCurrentTime(model, &tcur);
  // }
  double x = oms_getReal(model, "HelloWorld.x");
  oms_terminate(model);
  oms_unload(model);

  return x;
}

int test_cs_HelloWorld() {

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
  // Fit it to the graph
  auto fitResPtr = gexpect->Fit(&fode2, "S");
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

  return 0;
}
