#include <iostream>
#include <memory>

#include "src/simunits/fmi20/FMU20.h"
#include "src/simunits/system/CompositeSimUnit.h"
#include "src/simunits/system/Connector.h"

#include "src/simunits/fmi20/OutputRealPort.h"
#include "src/simunits/core/ISimUnit.h"

#include "src/simunits/stubs/SimController.h"

using namespace simunits;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::shared_ptr;

int main() {

  std::string sourceApath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string sourceBpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string adderpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_adder1.fmu";

  std::cout << "Creating sourceA ..." << std::endl;
  shared_ptr<fmi20::FMU20> sourceA(make_shared<fmi20::FMU20>(sourceApath, fmi20::kUnknown, "sourceA"));
  std::cout << "sourceA os: " << *sourceA << std::endl;

  std::cout << "Creating sourceB ..." << std::endl;
  shared_ptr<fmi20::FMU20> sourceB(make_shared<fmi20::FMU20>(sourceBpath));
  std::cout << "sourceB os: " << *sourceB << std::endl;

  std::cout << "Creating adder ..." << std::endl;
  shared_ptr<fmi20::FMU20> adder(make_shared<fmi20::FMU20>(adderpath));
  std::cout << "adder os: " << *adder << std::endl;

  std::cout << "Creating simunits container ..." << std::endl;

  system::CompositeSimUnit::SimUnitsContainer simunits = {sourceA, sourceB, adder};
  system::CompositeSimUnit::SimUnitsContainerPtr simunitsptr(make_shared<system::CompositeSimUnit::SimUnitsContainer>(simunits));

  std::cout << "Create connection sourceA.y -> adder.x1 ..." << std::endl;
  //system::Connector c_sourceA_y__adder_x1(sourceAports->at(0), adderports->at(0), "sourceA.y->adder.x1");
  shared_ptr<system::Connector> c_sourceA_y__adder_x1(make_shared<system::Connector>(sourceA->ports()->at(0), adder->ports()->at(0), "sourceA.y->adder.x1"));
  std::cout << "c_sourceA_y__adder_x1: " << *c_sourceA_y__adder_x1 << std::endl;

  std::cout << "Create connection sourceB.y -> adder.x2 ..." << std::endl;
  shared_ptr<system::Connector> c_sourceB_y__adder_x2(make_shared<system::Connector>(sourceB->ports()->at(0), adder->ports()->at(1), "sourceB.y->adder.x2"));
  std::cout << "c_sourceB_y__adder_x1: " << *c_sourceB_y__adder_x2 << std::endl;

  std::cout << "Creating connectors container ..." << std::endl;
  system::CompositeSimUnit::ConnectorsContainer connectors = {
    c_sourceA_y__adder_x1,
    c_sourceB_y__adder_x2
  };
  system::CompositeSimUnit::ConnectorsContainerPtr connectorsptr = make_shared<system::CompositeSimUnit::ConnectorsContainer>(connectors);

  std::cout << "Creating composite ..." << std::endl;
  //system::CompositeSimUnit::PortContainer* pmyports = fmu20.ports();
  system::CompositeSimUnit composite(simunitsptr, connectorsptr);
  std::cout << "composite os: " << composite << std::endl;

  std::cout << "sourceA.y.get: " << dynamic_pointer_cast<fmi20::OutputRealPort>(sourceA->ports()->at(0))->get() << std::endl;

  stubs::SimController simctrl;
  simctrl.simulate(&composite);
}
