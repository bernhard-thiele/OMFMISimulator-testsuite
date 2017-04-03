#include <iostream>
#include <memory>

#include "src/simunits/fmi20/FMU20ME.h"
#include "src/simunits/fmi20/SimUnitFMU20.h"

#include "src/simunits/fmi20/FMU20SimUnit.h"
#include "src/simunits/fmi20/ImportContext.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";
  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/MyTestReal.fmu";

  std::cout << "Creating fmu20me ..." << std::endl;
  fmi20::FMU20ME fmu20me(modelpath);
  std::cout << "My name: " << fmu20me.get_model_name() << std::endl;
  fmu20me.get_type_definitions();

  std::cout << "Creating SimUnitFMU20<fmi20::FMU20ME> ..." << std::endl;
  fmi20::SimUnitFMU20<fmi20::FMU20ME> simunit(modelpath);
  std::cout << "My name " << simunit.name() << std::endl;
  std::cout << "My GUID " << simunit.get_GUID() << std::endl;

  std::cout << "Creating FMU20SimUnit ..." << std::endl;
  fmi20::ImportContext* myimp = new fmi20::ImportContext(modelpath);
  fmi20::FMU20SimUnit fmu20simunit(myimp);
  std::cout << "My name " << fmu20simunit.name() << std::endl;
  std::cout << fmu20simunit << std::endl;

}
