#include <iostream>

#include "src/simunits/core/SimUnit.h"
#include "src/simunits/core/Port.h"
#include "src/simunits/core/CompositeSimUnit.h"
#include "src/simunits/core/Connector.h"

using namespace simunits;

int main() {

  std::cout << "Creating simunit ..." << std::endl;
  core::SimUnit simUnit;
  std::cout << "Instantiated SimUnit with default name: " << simUnit.name() << std::endl;
  simUnit.name("MySimUnitNewName"); // setting new name

  std::cout << std::endl << "Creating ports ..." << std::endl;
  core::Port port1;
  core::Port port2("MyPortName");
  std::vector<core::Port> myports;
  myports.push_back(port1);
  myports.push_back(port2);
  simUnit.ports(myports);

  std::cout << "Iterating over ports of SimUnit: " << std::endl;
  std::vector<core::Port>::iterator iter;
  // NOT WORKING!?
  // for (iter = myports.begin(); iter != myports.end(); iter++) {
  //   std::cout << iter->name() << std::endl;
  // }
  std::vector<core::Port> myports2  = simUnit.ports();
  for (iter = myports2.begin(); iter != myports2.end(); iter++) {
    std::cout << iter->name() << std::endl;
  }

  std::cout << std::endl << "Creating CompositeSimUnit ..." << std::endl;
  core::CompositeSimUnit compositeSimUnit("MyComposite");
  std::cout << "Instantiated CompositeSimUnit with name: " << compositeSimUnit.name() << std::endl;

  std::cout << std::endl << "Adding SimUnit to CompositeSimUnit ..." << std::endl;
  std::vector<core::SimUnit*> mySimUnits;
  mySimUnits.push_back(&simUnit);
  compositeSimUnit.simUnits(mySimUnits);

  std::cout << std::endl << "Creating Connector ..." << std::endl;
  core::Connector connector("myConnect");
  std::cout << "Instantiated Connector with name: " << connector.name() << std::endl;
  std::cout << "Connecting Connector to ports ..." << std::endl;
  connector.port_a(&port1);
  connector.port_b(&port2);
  std::cout << "Adding Connector to CompositeSimUnit ..." << std::endl;
  std::vector<core::Connector> myConnectors;
  compositeSimUnit.connectors(myConnectors);

  std::cout << std::endl << "Traversing the CompositeSimUnit ..." << std::endl;
  std::vector<core::SimUnit*>::iterator iter1;
  std::vector<core::SimUnit*> mySimUnits2 = compositeSimUnit.simUnits();
  for (iter1 = mySimUnits2.begin(); iter1 != mySimUnits2.end(); iter1++) {
    std::cout << "Simunit: " << (*iter1)->name() << std::endl << "\twith ports: " << std::endl;
    std::vector<core::Port> myports3 = (*iter1)->ports();
    std::vector<core::Port>::iterator iter2;
    for (iter2 = myports3.begin(); iter2 != myports3.end(); iter2++) {
      std::cout << "\t" << iter2->name() << std::endl;
    }
  }
  std::vector<core::Connector>::iterator iter3;
  std::vector<core::Connector> myConnectors2 = compositeSimUnit.connectors();
  for (iter3 = myConnectors2.begin(); iter3 != myConnectors2.end(); iter3++) {
    std::cout << "Connector: " << iter3->name() << "(" << iter3->port_a()->name() <<
      ", " << iter3->port_b()->name() <<  ")" << std::endl;
  }


  // for(auto p : simUnit.iterator) {
  //
  // }
}
