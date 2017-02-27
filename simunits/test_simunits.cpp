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
  simUnit.push_back(port1);
  core::Port port2("MyPortName");
  simUnit.push_back(port2);

  std::cout << "Iterating over ports of SimUnit: " << std::endl;
  core::SimUnit::iterator iter;
  for (iter = simUnit.begin(); iter != simUnit.end(); iter++) {
    std::cout << iter->name() << std::endl;
  }

  std::cout << std::endl << "Creating CompositeSimUnit ..." << std::endl;
  core::CompositeSimUnit compositeSimUnit("MyComposite");
  std::cout << "Instantiated CompositeSimUnit with name: " << compositeSimUnit.name() << std::endl;

  std::cout << std::endl << "Adding SimUnit to CompositeSimUnit ..." << std::endl;
  compositeSimUnit.simunit_push_back(&simUnit);

  std::cout << std::endl << "Creating Connector ..." << std::endl;
  core::Connector connector("myConnect");
  std::cout << "Instantiated Connector with name: " << connector.name() << std::endl;
  std::cout << "Connecting Connector to ports ..." << std::endl;
  connector.port_a(&port1);
  connector.port_b(&port2);
  std::cout << "Adding Connector to CompositeSimUnit ..." << std::endl;
  compositeSimUnit.connector_push_back(connector);

  std::cout << std::endl << "Traversing the CompositeSimUnit ..." << std::endl;
  core::CompositeSimUnit::simunit_iterator iter1;
  for (iter1 = compositeSimUnit.simunit_begin(); iter1 != compositeSimUnit.simunit_end(); iter1++) {
    std::cout << "Simunit: " << (*iter1)->name() << std::endl << "\twith ports: " << std::endl;
    core::SimUnit::iterator iter2;
    for (iter2 = (*iter1)->begin(); iter2 != (*iter1)->end(); iter2++) {
      std::cout << "\t" << iter2->name() << std::endl;
    }
  }
  core::CompositeSimUnit::connector_iterator iter3;
  for (iter3 = compositeSimUnit.connector_begin(); iter3 != compositeSimUnit.connector_end(); iter3++) {
    std::cout << "Connector: " << iter3->name() << "(" << iter3->port_a()->name() <<
      ", " << iter3->port_b()->name() <<  ")" << std::endl;
  }


  // for(auto p : simUnit.iterator) {
  //
  // }
}
