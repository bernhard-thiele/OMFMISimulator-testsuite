#include <iostream>

#include "src/simunits/fmi20/FMU20.h"
#include "src/simunits/core/Port.h"
#include "src/simunits/core/CompositeSimUnit.h"
#include "src/simunits/core/Connector.h"

using namespace simunits;

int main() {

  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";

  std::cout << "Creating simunit ..." << std::endl;
  fmi20::FMU20 simUnit(modelpath);
  std::cout << "Instantiated SimUnit name: " << simUnit.name << std::endl;

  simUnit.simulate_cs();
}
