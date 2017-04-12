#include <iostream>
#include <memory>

#include "src/simunits/fmi20/FMU20.h"

#include "src/simunits/fmi20/OutputRealPort.h"
// #include "src/simunits/core/CompositeSimUnit.h"
// #include "src/simunits/core/Connector.h"
#include "src/simunits/core/ISimUnit3.h"

#include "src/simunits/stubs/SimController.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";
  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/MyTestReal.fmu";

  std::cout << "Creating fmu20 ..." << std::endl;
  fmi20::FMU20 fmu20(modelpath);
  std::cout << "Instantiated FMU20 name: " << fmu20.name() << std::endl;
  std::cout << "Instantiated FMU20 os: " << fmu20 << std::endl;
  fmi20::FMU20::PortsPtr pmyports = fmu20.ports();
  for (auto i=pmyports->begin(); i != pmyports->end(); i++) {
    if ((*i)->kind() == simunits::core::ScalarOutputReal) {
      fmi20::OutputRealPortPtr p = std::dynamic_pointer_cast<fmi20::OutputRealPort>(*i);
      double x = p->get();
      std::cout << "got: " << (*i)->toString() << " value=" << x << std::endl;
    }
  }



  stubs::SimController simctrl;
  simctrl.simulate(&fmu20);

  //////////////////
  core::ISimUnit3 s2(pmyports->begin(), pmyports->end());
  std::cout << s2.toString() << std::endl;
  for (auto i=s2.portBegin(); i != s2.portEnd(); ++i) {
    std::cout << "Got Port: " << (*i)->toString() << std::endl;
  }
  std::cout << "Got by key: " << s2["oreal1"]->toString() << std::endl;
  std::cout << "Got by port_at: " << s2.port_at("oreal2")->toString() << std::endl;
  auto it = s2.port_find("oreal1");
  if (it != s2.port_mapend()) {
    std::cout << "By using find: " << it->second->toString() << std::endl;
  }
  if (auto it = s2.port_find("dont exists") != s2.port_mapend()) {
    std::cout << "never get here\n";
  }
}
