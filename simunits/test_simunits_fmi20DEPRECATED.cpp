#include <iostream>

#include "src/simunits/fmi20/FMU20L.h"

#include "src/simunits/fmi20/OutputRealPortDeprecated.h"
// #include "src/simunits/core/CompositeSimUnit.h"
// #include "src/simunits/core/Connector.h"

#include "src/simunits/stubs/SimControllerDEPRECATED.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";
  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/MyTestReal.fmu";

  fmi20::OutputRealPortDeprecated outRp("Testme");
  std::cout << "Instantiated OutputRealPort name: " << outRp.name() << std::endl;
  std::cout << "Instantiated OutputRealPort os: " << outRp << std::endl;

  std::cout << "Creating fmu20 ..." << std::endl;
  fmi20::FMU20L fmu20(modelpath);
  std::cout << "Instantiated FMU20L name: " << fmu20.name() << std::endl;
  std::cout << "Instantiated FMU20L os: " << fmu20 << std::endl;
  fmi20::FMU20L::PortContainer* pmyports = fmu20.ports();
  for (auto i=pmyports->begin(); i != pmyports->end(); i++) {
    if ((*i)->kind() == simunits::core::ScalarOutputReal) {
      fmi20::OutputRealPortDeprecated* p = (fmi20::OutputRealPortDeprecated*) (*i);
      double x = p->get();
      std::cout << "got: " << (*i)->toString() << " value=" << x << std::endl;
    }
  }

  stubs::SimControllerDEPRECATED simctrl;
  //simctrl.simulate(&fmu20);

  // ugly ... just to have print
  // fmi20::FMU20L::PortContainer myports;
  // myports.push_back(&outRp);
  // fmu20.ports(myports);
  // std::cout << "Instantiated FMU20L os: " << fmu20 << std::endl;
}
