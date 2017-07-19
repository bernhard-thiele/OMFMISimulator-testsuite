#!/usr/bin/lua
-- name: me_test1
-- status: correct

if os.getenv("OS") == "Windows_NT" then
  package.cpath = package.cpath .. ';../../install/lib/?.dll'
else
  package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
end
require("OMSimulatorLua")

version = getVersion()
-- print(version)
model = newModel()
setTempDirectory(".")

instantiateFMU(model, "../FMUs/me_test1.fmu", "test1")
describe(model)

setStopTime(model, 2.1)
setTolerance(model, 1e-5)

initialize(model)
simulate(model)
terminate(model)

unload(model)

-- Result:
-- # FMU instances
-- test1
--   - FMI 2.0 ME
--   - path: ../FMUs/me_test1.fmu
--   - GUID: {5daf3328-7e1e-4ed4-af75-84ebb83eb29e}
--   - tool: OpenModelica Compiler OMCompiler v1.12.0-dev.395+gdeeabde
--   - input interface:
--   - output interface:
--
-- # Simulation settings
--   - start time: <undefined>
--   - stop time: <undefined>
--   - tolerance: <undefined>
--   - communication interval: <undefined>
--   - result file: <no result file>
--
-- # Composite structure
-- ## Initialization
--
-- ## Simulation
--
-- endResult
