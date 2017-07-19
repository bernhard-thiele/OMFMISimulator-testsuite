// Experiment for fitting functions / parameter estimation
// Let's try fiting OMC ODE parameters to a reference OMC ODE solution
// WORKS BUT VERY SLOW! Compare speed to test_cfunc_HelloWorld.C


#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string>
#include <sstream>
#include <unistd.h>

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
  static int count = 0;
  count++;
  std::cout << "N" << count << std::endl;

  // Need to be in executable dir it seems ...
  // getcwd (char *__buf, size_t __size)
  chdir("models/simbin_HelloWorld");

  std::ostringstream oscmd;
  oscmd << "./HelloWorld -override x_start=" << pars[0] <<
    ",a=" << pars[1] << ",stopTime=" << vars[0] << " -output x -noemit";
  std::string cmd = oscmd.str();
  // std::cout << "Calling " << cmd << std::endl;
  std::string result = exec(cmd.c_str());
  // std::cout << "Got: " << result << std::endl;
  // sscanf is so complicated ...
  std::string result2 = result.substr(5);
  //std::cout << "Starting with: " << result2 << std::endl;
  std::istringstream isresult(result2);
  double simtime; std::string rest; double x;
  isresult >> simtime >> rest;
  std::string result3 = rest.substr(3);
  isresult.str(result3);
  isresult >> x;
  //std::cout << "Extracted - time: " << simtime << " x: " << x << std::endl;

  chdir("../..");
  return x;
}

int test_simbin_HelloWorld() {

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
