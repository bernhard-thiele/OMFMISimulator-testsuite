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
-- GUID: {e72ab90f-3c54-4c60-a423-177dbaddd14c}
-- Model identifier for CS: cs_test1
-- endResult
