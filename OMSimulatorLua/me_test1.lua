#!/usr/bin/lua
-- name: me_test1
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

version = getVersion()
-- print(version)

setWorkingDirectory(".")

model = newModel()
instantiateFMU(model, "../FMUs/me_test1.fmu", "test1")
describe(model)

setStopTime(2.1)
setTolerance(1e-5)

simulate(model)

unload(model)

-- Result:
-- test1
-- Model name: test1
-- GUID: {20db05bd-be73-4960-aaa8-ee4be1af214a}
-- Model identifier for ME: me_test1
-- endResult
