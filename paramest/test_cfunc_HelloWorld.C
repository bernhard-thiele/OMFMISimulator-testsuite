// Experiment for fitting functions / parameter estimation
// Let's try fiting ODE parameters to a reference ODE solution

// der(x) = p[1]*x;
// x(0) = p[0];
double the_ode(double* vars, double* pars){
  double x = pars[0];
  double Ts = 0.1;
  for (double t=0; t <= vars[0]; t += Ts) {
    x = x + Ts*pars[1]*x;
  }
  return x;
}

int test_cfunc_HelloWorld() {

  TCanvas *c1 = new TCanvas("c1","tofind",700,500);

  TF1 fode1("ODE;time;Y Vals",the_ode,0,10,2);
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
  TF1 fode2("fittet ODE;time;Y Vals",the_ode,0,10,2);
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
  leg.AddEntry(gexpect,"Exp. ODE solution");
  leg.AddEntry(&fode2,"Fitted function");
  leg.DrawClone("Same");


  return 0;
}
