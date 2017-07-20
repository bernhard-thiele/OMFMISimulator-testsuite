// name: test_cs_BouncingBall
// status: correct

/** Before the script runs in root, one needs to load the OMSimulator shared library on the REPL
 *
 * gSystem->Load("../../3rdParty/FMIL/install/linux/lib/libfmilib_shared.so");
 * gSystem->Load("../../install/lib/libOMSimulatorLib.so");
 */

#include "../../install/include/OMSimulator.h"

void test_cs_BouncingBall() {
  const char* version = oms_getVersion();
  //std::cout << version << std::endl;

  void* model = oms_newModel();
  oms_setTempDirectory(".");

  oms_instantiateFMU(model, "../FMUs/cs_BouncingBall.fmu", "BouncingBall");
  oms_describe(model);

  oms_setStopTime(model, 2.1);
  oms_setTolerance(model, 1e-5);

  oms_initialize(model);
  oms_simulate(model);

  oms_unload(model);
}

// Result:
//
// Processing test_cs_BouncingBall.C...
// # FMU instances
// BouncingBall
//   - FMI 2.0 CS
//   - path: ../FMUs/cs_BouncingBall.fmu
//   - GUID: {ed0c3e8c-c48f-4995-b80b-eb1d54c9737b}
//   - tool: OpenModelica Compiler OMCompiler v1.12.0-dev.395+gdeeabde
//   - input interface:
//   - output interface:
//
// # Simulation settings
//   - start time: <undefined>
//   - stop time: <undefined>
//   - tolerance: <undefined>
//   - communication interval: <undefined>
//   - result file: <no result file>
//
// # Composite structure
// ## Initialization
//
// ## Simulation
//
// endResult
