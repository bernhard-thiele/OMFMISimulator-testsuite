#include <iostream>

#include "src/simunits/stubs/SimController.h"
#include "src/simunits/ObjectFactory.h"

using namespace simunits;

int main() {

  std::string sourceApath = "/home/bernhard/data/workspace/OMFMISimulator/testsuite/FMUs/me_source1.fmu";
  std::string sourceBpath = "/home/bernhard/data/workspace/OMFMISimulator/testsuite/FMUs/me_source1.fmu";
  std::string adderpath = "/home/bernhard/data/workspace/OMFMISimulator/testsuite/FMUs/me_adder1.fmu";

  auto sourceA = createFMU20(sourceApath, fmi20::kUnknown, "sourceA");
  auto sourceB = createFMU20(sourceBpath);
  auto adder = createFMU20(adderpath);

  auto c_sourceA_y__adder_x1 = createConnector(sourceA->ports_at("y"), adder->ports_at("x1"));
  auto c_sourceB_y__adder_x2 = createConnector(sourceB->ports_at("y"), adder->ports_at("x2"));

  auto composite = createCompositeSimunit(
    {sourceA, sourceB, adder},
    {c_sourceA_y__adder_x1, c_sourceB_y__adder_x2},
    {}
  );

  std::cout << "composite: " << *composite << std::endl;

  stubs::SimController simctrl;
  simctrl.simulate(composite);
}
