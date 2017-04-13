#include <iostream>
#include <memory>
#include <algorithm>

#include "src/simunits/fmi20/FMU20.h"

#include "src/simunits/fmi20/OutputRealPort.h"
// #include "src/simunits/core/CompositeSimUnit.h"
// #include "src/simunits/core/Connector.h"
#include "src/simunits/core/ISimUnit3.h"

#include "src/simunits/stubs/SimController.h"

using namespace simunits;

int main() {

  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_BouncingBall.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/cs_PID_Controller.fmu";
  //std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/me_BouncingBall.fmu";
  std::string modelpath = "/home/bernhard/data/workspace/OMSimulator/testsuite/FMUs/MyTestReal.fmu";

  std::cout << "Creating fmu20 ..." << std::endl;
  fmi20::FMU20 fmu20(modelpath);
  std::cout << "Instantiated FMU20 name: " << fmu20.name() << std::endl;
  std::cout << "Instantiated FMU20 os: " << fmu20 << std::endl;
  fmi20::FMU20::PortsPtr pmyports = fmu20.ports();
  for (auto i=pmyports->begin(); i != pmyports->end(); i++) {
    if ((*i)->kind() == simunits::core::ScalarOutputReal) {
      fmi20::OutputRealPortPtr p = std::dynamic_pointer_cast<fmi20::OutputRealPort>(*i);
      double x = p->get();
      std::cout << "got: " << (*i)->toString() << " value=" << x << std::endl;
    }
  }



  stubs::SimController simctrl;
  simctrl.simulate(&fmu20);

  //////////////////
  core::ISimUnit3 s2(pmyports->begin(), pmyports->end());
  std::cout << s2.toString() << std::endl;
  for (auto i=s2.portBegin(); i != s2.portEnd(); ++i) {
    std::cout << "Got Port: " << (*i)->toString() << std::endl;
  }
  std::cout << "Got by key: " << s2["oreal1"]->toString() << std::endl;
  std::cout << "Got by port_at: " << s2.port_at("oreal2")->toString() << std::endl;
  auto it = s2.port_find("oreal1");
  if (it != s2.port_mapend()) {
    std::cout << "By using find: " << it->second->toString() << std::endl;
  }
  if (auto it = s2.port_find("dont exists") != s2.port_mapend()) {
    std::cout << "never get here\n";
  }

  ///////////////////
  std::cout << "TEST COMPARISON AND SORTING\n";
  core::Idn idn1("idn1");
  core::Idn idn2("idn2");
  core::Idn idn3("idn3");
  std::cout << "We have Idns " << idn1 << " " << idn2 << " " << idn3 << std::endl;
  if (idn1 == idn2) std::cout << "UUPS " << idn1 << " == " << idn2 << std::endl;
  if (idn1 == idn1) std::cout << idn1 << " == " << idn1 << std::endl;
  if (idn1 < idn2) std::cout << idn1 << " < " << idn2 << std::endl;
  if (idn3 < idn2) std::cout << "UUPS " << idn3 << " < " << idn2 << std::endl;
  std::vector<core::Idn> idnvec{idn3, idn1, idn2};
  for (auto a : idnvec) std::cout << ", " << a;
  std::cout << std::endl;
  std::sort(idnvec.begin(), idnvec.end());
  for (auto a : idnvec) std::cout << ", " << a;
  std::cout << std::endl;
  core::Dot dot1(std::make_shared<core::Idn>("pre"),std::make_shared<core::Idn>("idn1"));
  core::Dot dot2(std::make_shared<core::Idn>("pre"),std::make_shared<core::Idn>("idn2"));
  core::Dot dot3(std::make_shared<core::Idn>("pzz"),std::make_shared<core::Idn>("idn1"));
  std::cout << "We have Dots " << dot1 << "; " << dot2 << "; " << dot3 << std::endl;
  if (dot1 == dot2) std::cout << "UUPS " << dot1 << " == " << dot2 << std::endl;
  if (dot1 == dot1) std::cout << dot1 << " == " << dot1 << std::endl;
  if (dot1 < dot2) std::cout << dot1 << " < " << dot2 << std::endl;
  if (dot3 < dot1) std::cout << "UUPS " << dot3 << " < " << dot1 << std::endl;
  if (dot3 < dot2) std::cout << "UUPS " << dot3 << " < " << dot2 << std::endl;
  std::vector<core::Dot> dotvec{dot3, dot2, dot1};
  for (auto a : dotvec) std::cout << ", " << a;
  std::cout << std::endl;
  std::sort(dotvec.begin(), dotvec.end());
  for (auto a : dotvec) std::cout << ", " << a;
  std::cout << "\nWe have DotPtrs\n";
  auto dotptr1 = std::make_shared<core::Dot>(std::make_shared<core::Idn>("pre"),std::make_shared<core::Idn>("idn1"));
  auto dotptr2 = std::make_shared<core::Dot>(std::make_shared<core::Idn>("pre"),std::make_shared<core::Idn>("idn2"));
  auto dotptr3 = std::make_shared<core::Dot>(std::make_shared<core::Idn>("pzz"),std::make_shared<core::Idn>("idn1"));
  std::vector<std::shared_ptr<core::Dot> > dotptr{dotptr3,dotptr2,dotptr1};
  for (auto a : dotptr) std::cout << ", " << *a;
  std::cout << std::endl;
  std::sort(dotptr.begin(), dotptr.end(), [](std::shared_ptr<core::Identifier> a, std::shared_ptr<core::Identifier> b) {return *a < *b;});
  for (auto a : dotptr) std::cout << ", " << *a;
  std::cout << std::endl;
}
