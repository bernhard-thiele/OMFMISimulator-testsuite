#!/usr/bin/lua
-- name: cs_test1
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
setWorkingDirectory(model, ".")

instantiateFMU(model, "../FMUs/cs_test1.fmu", "test1")
describe(model)

setStopTime(model, 2.1)
setTolerance(model, 1e-5)

simulate(model)

unload(model)

-- Result:
-- # FMU instances
-- test1
--   - FMI 2.0 CS
--   - path: ../FMUs/cs_test1.fmu
--   - GUID: {e72ab90f-3c54-4c60-a423-177dbaddd14c}
--
-- # Simulation settings
--   - start time: 0
--   - stop time: 0
--   - tolerance: 0
--   - result file: <no result file>
--
-- # Composite structure
-- ## Initialization
--
-- ## Simulation
--
-- endResult
