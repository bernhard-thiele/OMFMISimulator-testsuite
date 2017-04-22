#include <iostream>
#include <memory>

#include "src/simunits/fmi20/FMU20.h"
#include "src/simunits/system/CompositeSimunit.h"
#include "src/simunits/system/Connector.h"
#include "src/simunits/system/ScalarInputRealPort.h"

#include "src/simunits/fmi20/OutputRealPort.h"
#include "src/simunits/core/ISimunit.h"

#include "src/simunits/stubs/SimController.h"

using namespace simunits;
using std::make_shared;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::shared_ptr;

int main() {

  std::string sourceApath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string sourceBpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_source1.fmu";
  std::string adderpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_adder1.fmu";

  std::cout << "Creating sourceA ..." << std::endl;
  auto sourceA = make_shared<fmi20::FMU20>(sourceApath, fmi20::kUnknown, "sourceA");
  std::cout << "sourceA os: " << *sourceA << std::endl;

  std::cout << "Creating adder ..." << std::endl;
  auto adder(make_shared<fmi20::FMU20>(adderpath));
  std::cout << "adder os: " << *adder << std::endl;

  std::cout << "Creating composite port u ...\n";
  auto p_u = make_shared<system::ScalarInputRealPort>("u");

  std::cout << "Creating inner connections..." << std::endl;
  auto c_sourceA_y__adder_x1 = make_shared<system::Connector>(sourceA->ports_at("y"), adder->ports_at("x1"), "sourceA.y->adder.x1");
  auto c_u__adder_x2 = make_shared<system::Connector>(p_u, adder->ports()->at(1), "u->adder.x2");

  std::cout << "Creating composite comp1 ..." << std::endl;
  std::initializer_list<core::ISimunitPtr> simunits = {sourceA, adder};
  std::initializer_list<core::IConnectorPtr> connectors = {c_sourceA_y__adder_x1, c_u__adder_x2};
  std::initializer_list<core::IPortPtr> ports = {p_u};
  auto comp1 = make_shared<system::CompositeSimunit>(simunits, connectors, ports, "comp1");
  std::cout << "comp1 os: " << *comp1 << std::endl;

  stubs::SimController simctrl;
  auto p_dyn = comp1->getDynPort();
  std::cout << "Inserting dependency to ISolver (FIXME revise mechanism): " << std::endl;
  p_dyn->setRequiredISolver(&simctrl);


  std::cout << "Creating sourceB ..." << std::endl;
  auto sourceB = make_shared<fmi20::FMU20>(sourceBpath);
  std::cout << "sourceB os: " << *sourceB << std::endl;

  std::cout << "Creating outer connections..." << std::endl;
  auto c_sourceB_y__u = make_shared<system::Connector>(sourceB->ports_at("y"), comp1->ports_at("u"), "sourceB.y->comp1.u");

  std::cout << "Creating composite context ..." << std::endl;
  std::initializer_list<core::ISimunitPtr> simunits2 = {sourceB, comp1};
  std::initializer_list<core::IConnectorPtr> connectors2 = {c_sourceB_y__u};
  std::initializer_list<core::IPortPtr> ports2 = {};
  //system::CompositeSimunit composite(simunits, connectors, ports);
  auto context = make_shared<system::CompositeSimunit>(simunits2, connectors2, ports2, "context");
  std::cout << "context os: " << *context << std::endl;

  simctrl.simulate(context.get());
}
