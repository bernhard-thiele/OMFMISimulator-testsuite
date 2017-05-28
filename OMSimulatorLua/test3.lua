#!/usr/bin/lua
-- name: test3
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

version = getVersion()
-- print(version)

model = newModel()
setWorkingDirectory(model, ".")

-- instantiate FMUs
instantiateFMU(model, "../FMUs/me_source1.fmu", "sourceA")
instantiateFMU(model, "../FMUs/me_source1.fmu", "sourceB")
instantiateFMU(model, "../FMUs/me_adder1.fmu", "adder")

-- add connections
addConnection(model, "sourceA.y", "adder.x1")
addConnection(model, "sourceB.y", "adder.x2")

-- set parameter
setReal(model, "sourceA.A", 0.5)
setReal(model, "sourceA.omega", 2.0)

setStopTime(model, 0.0)
--setStopTime(model, 10.0)

initialize(model)
tcur = getCurrentTime(model)
while tcur < 10.0
do
  doSteps(model, 1)
  tcur = getCurrentTime(model)
end
print("sourceA.y at " .. tcur .. ": " .. getReal(model, "sourceA.y"))
print("sourceB.y at " .. tcur .. ": " .. getReal(model, "sourceB.y"))
terminate(model)

unload(model)

-- Result:
-- sourceA.y at 10.1: 0.45647262536381
-- sourceB.y at 10.1: -0.54402111088935
-- endResult
