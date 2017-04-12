#include <iostream>
#include <memory>

#include "src/simunits/fmi20/FMU20.h"
#include "src/simunits/system/CompositeSimUnit.h"
#include "src/simunits/system/Connector.h"

#include "src/simunits/fmi20/OutputRealPort.h"
#include "src/simunits/core/ISimunit.h"

#include "src/simunits/stubs/SimController.h"

#include "src/simunits/ObjectFactory.h"

using namespace simunits;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::shared_ptr;

int main() {

  std::string sourceApath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string sourceBpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string adderpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_adder1.fmu";

  std::cout << "Creating sourceA ..." << std::endl;
  shared_ptr<fmi20::FMU20> sourceA = createFMU20(sourceApath, fmi20::kUnknown, "sourceA");
  std::cout << "sourceA os: " << *sourceA << std::endl;

  std::cout << "Creating sourceB ..." << std::endl;
  shared_ptr<fmi20::FMU20> sourceB = createFMU20(sourceBpath);
  std::cout << "sourceB os: " << *sourceB << std::endl;

  std::cout << "Creating adder ..." << std::endl;
  shared_ptr<fmi20::FMU20> adder = createFMU20(adderpath);
  std::cout << "adder os: " << *adder << std::endl;

  std::cout << "Creating simunits container ..." << std::endl;
  // system::CompositeSimUnit::SimunitsPtr simunitsp = createSimUnits({sourceA, sourceB, adder}); // NOPE
  auto simunits2 = {sourceA, sourceB, adder};
  // system::CompositeSimUnit::SimunitsPtr simunitsp = createSimUnits(simunits2); // NOPE

  system::CompositeSimUnit::Simunits simunits = {sourceA, sourceB, adder};
  system::CompositeSimUnit::SimunitsPtr simunitsptr(make_shared<system::CompositeSimUnit::Simunits>(simunits));
  // alternative syntax
  system::CompositeSimUnit::SimunitsPtr simunitsptr2(new system::CompositeSimUnit::Simunits({sourceA, sourceB, adder}));

  std::cout << "Create connection sourceA.y -> adder.x1 ..." << std::endl;
  //system::Connector c_sourceA_y__adder_x1(sourceAports->at(0), adderports->at(0), "sourceA.y->adder.x1");
  shared_ptr<system::Connector> c_sourceA_y__adder_x1(make_shared<system::Connector>(sourceA->ports()->at(0), adder->ports()->at(0), "sourceA.y->adder.x1"));
  std::cout << "c_sourceA_y__adder_x1: " << *c_sourceA_y__adder_x1 << std::endl;

  std::cout << "Create connection sourceB.y -> adder.x2 ..." << std::endl;
  shared_ptr<system::Connector> c_sourceB_y__adder_x2(make_shared<system::Connector>(sourceB->ports()->at(0), adder->ports()->at(1), "sourceB.y->adder.x2"));
  std::cout << "c_sourceB_y__adder_x1: " << *c_sourceB_y__adder_x2 << std::endl;

  std::cout << "Creating connectors container ..." << std::endl;
  system::CompositeSimUnit::Connectors connectors = {
    c_sourceA_y__adder_x1,
    c_sourceB_y__adder_x2
  };
  system::CompositeSimUnit::ConnectorsPtr connectorsptr = make_shared<system::CompositeSimUnit::Connectors>(connectors);

  std::cout << "Creating composite ..." << std::endl;
  //system::CompositeSimUnit::PortContainer* pmyports = fmu20.ports();
  system::CompositeSimUnit composite(simunitsptr, connectorsptr);
  std::cout << "composite os: " << composite << std::endl;

  std::cout << "sourceA.y.get: " << dynamic_pointer_cast<fmi20::OutputRealPort>(sourceA->ports()->at(0))->get() << std::endl;

  stubs::SimController simctrl;
  simctrl.simulate(&composite);
}
