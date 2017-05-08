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
-- BouncingBall
-- Model name: BouncingBall
-- GUID: {35ad3480-034b-4cbf-9396-c17a51220ee7}
-- Model identifier for ME: me_BouncingBall
-- endResult
