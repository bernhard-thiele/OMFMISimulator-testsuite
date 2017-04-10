#!/usr/bin/lua
-- name: cs_test1
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

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
-- test1
-- Model name: test1
-- GUID: {010f91f9-a1ae-45cc-974a-2d37dc3380d9}
-- Model identifier for CS: cs_test1
-- endResult
