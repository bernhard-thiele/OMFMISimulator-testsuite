#!/usr/bin/lua
-- name: cs_BouncingBall
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

version = getVersion()
-- print(version)

model = newModel()
setWorkingDirectory(model, ".")

instantiateFMU(model, "../FMUs/cs_BouncingBall.fmu", "BouncingBall")
describe(model)

setStopTime(model, 2.1)
setTolerance(model, 1e-5)

simulate(model)

unload(model)

-- Result:
-- BouncingBall
-- Model name: BouncingBall
-- GUID: {7ee6661b-d1b8-4708-aa70-efe07ecd931e}
-- Model identifier for CS: cs_BouncingBall
-- endResult
