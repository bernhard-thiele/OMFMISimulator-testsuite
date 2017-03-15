#include <iostream>

#include "src/simunits/fmi20/FMU20.h"

#include "src/simunits/fmi20/OutputRealPort.h"
// #include "src/simunits/core/CompositeSimUnit.h"
// #include "src/simunits/core/Connector.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";

  fmi20::OutputRealPort outRp("Testme");
  std::cout << "Instantiated OutputRealPort name: " << outRp.name() << std::endl;
  std::cout << "Instantiated OutputRealPort os: " << outRp << std::endl;


  std::cout << "Creating simunit ..." << std::endl;
  fmi20::FMU20 simUnit(modelpath);
  std::cout << "Instantiated SimUnit name: " << simUnit.name() << std::endl;

  //simUnit.simulate();
}
