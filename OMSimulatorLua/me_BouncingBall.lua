#!/usr/bin/lua
-- name: me_BouncingBall
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

version = getVersion()
-- print(version)

setWorkingDirectory(".")

model = newModel()
instantiateFMU(model, "../FMUs/me_BouncingBall.fmu", "BouncingBall")
describe(model)

setStopTime(2.1)
setTolerance(1e-5)

simulate(model)

unload(model)

-- Result:
-- BouncingBall
-- Model name: BouncingBall
-- GUID: {6a7dc7ae-436f-49e4-95f0-4888b7618f70}
-- Model identifier for ME: me_BouncingBall
-- endResult
