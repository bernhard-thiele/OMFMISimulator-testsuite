#include <iostream>

#include "src/simunits/fmi20/FMU20.h"
#include "src/simunits/system/CompositeSimUnit.h"
#include "src/simunits/system/Connector.h"

#include "src/simunits/fmi20/OutputRealPort.h"
// #include "src/simunits/core/CompositeSimUnit.h"
// #include "src/simunits/core/Connector.h"

#include "src/simunits/stubs/SimController.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";
  // std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/MyTestReal.fmu";
  std::string sourceApath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string sourceBpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string adderpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_adder1.fmu";

  std::cout << "Creating sourceA ..." << std::endl;
  fmi20::FMU20 sourceA(sourceApath);
  std::cout << "sourceA os: " << sourceA << std::endl;

  std::cout << "Creating sourceB ..." << std::endl;
  fmi20::FMU20 sourceB(sourceBpath);
  std::cout << "sourceB os: " << sourceB << std::endl;

  std::cout << "Creating adder ..." << std::endl;
  fmi20::FMU20 adder(adderpath);
  std::cout << "adder os: " << adder << std::endl;

  std::cout << "Creating simunits container ..." << std::endl;
  system::CompositeSimUnit::SimUnitsContainer simunits;
  simunits.push_back(&sourceA);
  simunits.push_back(&sourceB);
  simunits.push_back(&adder);

  std::cout << "Extracting ports of sourceA ..." << std::endl;
  fmi20::FMU20::PortContainer* sourceAports = sourceA.ports();
  std::cout << "Extracting ports of sourceB ..." << std::endl;
  fmi20::FMU20::PortContainer* sourceBports = sourceB.ports();
  std::cout << "Extracting ports of adder ..." << std::endl;
  fmi20::FMU20::PortContainer* adderports = adder.ports();

  std::cout << "Create connection sourceA.y -> adder.x1 ..." << std::endl;
  system::Connector c_sourceA_y__adder_x1(sourceAports->at(0), adderports->at(0), "sourceA.y->adder.x1");
  std::cout << "c_sourceA_y__adder_x1: " << c_sourceA_y__adder_x1 << std::endl;

  std::cout << "Create connection sourceB.y -> adder.x2 ..." << std::endl;
  system::Connector c_sourceB_y__adder_x2(sourceBports->at(0), adderports->at(1), "sourceB.y->adder.x2");
  std::cout << "c_sourceB_y__adder_x1: " << c_sourceB_y__adder_x2 << std::endl;

  std::cout << "Creating connectors container ..." << std::endl;
  system::CompositeSimUnit::ConnectorsContainer connectors;
  connectors.push_back(&c_sourceA_y__adder_x1);
  connectors.push_back(&c_sourceB_y__adder_x2);

  std::cout << "Creating composite ..." << std::endl;
  system::CompositeSimUnit composite(&simunits, &connectors);
  std::cout << "composite os: " << composite << std::endl;

  stubs::SimController simctrl;
  //??simctrl.simulate(&composite);
}
