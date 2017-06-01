#!/usr/bin/lua
-- name: me_BouncingBall
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

version = getVersion()
-- print(version)

model = newModel()
setWorkingDirectory(model, ".")

instantiateFMU(model, "../FMUs/me_BouncingBall.fmu", "BouncingBall")
describe(model)

setStopTime(model, 2.1)
setTolerance(model, 1e-5)

simulate(model)

unload(model)

-- Result:
-- # FMU instances
-- BouncingBall
--   - FMI 2.0 ME
--   - path: ../FMUs/me_BouncingBall.fmu
--   - GUID: {35ad3480-034b-4cbf-9396-c17a51220ee7}
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
