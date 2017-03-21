#include <iostream>

#include "src/simunits/fmi20/FMU20.h"

#include "src/simunits/fmi20/OutputRealPort.h"
// #include "src/simunits/core/CompositeSimUnit.h"
// #include "src/simunits/core/Connector.h"

#include "src/simunits/stubs/SimController.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";
  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/MyTestReal.fmu";

  fmi20::OutputRealPort outRp("Testme");
  std::cout << "Instantiated OutputRealPort name: " << outRp.name() << std::endl;
  std::cout << "Instantiated OutputRealPort os: " << outRp << std::endl;

  std::cout << "Creating fmu20 ..." << std::endl;
  fmi20::FMU20 fmu20(modelpath);
  std::cout << "Instantiated FMU20 name: " << fmu20.name() << std::endl;
  std::cout << "Instantiated FMU20 os: " << fmu20 << std::endl;
  fmi20::FMU20::PortContainer* pmyports = fmu20.ports();
  for (auto i=pmyports->begin(); i != pmyports->end(); i++) {
    if ((*i)->kind() == simunits::core::ScalarOutputReal) {
      fmi20::OutputRealPort* p = (fmi20::OutputRealPort*) (*i);
      double x = p->get();
      std::cout << "got: " << (*i)->toString() << " value=" << x << std::endl;
    }
  }

  stubs::SimController simctrl;
  //simctrl.simulate(&fmu20);

  // ugly ... just to have print
  // fmi20::FMU20::PortContainer myports;
  // myports.push_back(&outRp);
  // fmu20.ports(myports);
  // std::cout << "Instantiated FMU20 os: " << fmu20 << std::endl;
}
