#!/usr/bin/lua
-- name: me_test1
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

version = getVersion()
-- print(version)

model = newModel()
setWorkingDirectory(model, ".")

instantiateFMU(model, "../FMUs/me_test1.fmu", "test1")
describe(model)

setStopTime(model, 2.1)
setTolerance(model, 1e-5)

simulate(model)

unload(model)

-- Result:
-- # FMU instances
-- test1
--   - FMI 2.0 ME
--   - path: ../FMUs/me_test1.fmu
--   - GUID: {5daf3328-7e1e-4ed4-af75-84ebb83eb29e}
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
