#!/usr/bin/lua
-- name: cs_HelloWorld_Reset
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
setTempDirectory(".")

-- instantiate FMU
instantiateFMU(model, "../FMUs/cs_HelloWorld.fmu", "HelloWorld")

-- set parameter
setReal(model, "HelloWorld.x_start", 1.0)
setReal(model, "HelloWorld.a", -1.0)
setStopTime(model, 1.0)
-- initialize and simulate
initialize(model)
stepUntil(model, 1.0)
tcur = getCurrentTime(model)
print("Parametrization 1: HelloWorld.x at " .. tcur .. ": " .. getReal(model, "HelloWorld.x"))

-- reset FMU
reset(model)
-- set parameter
setReal(model, "HelloWorld.x_start", 0.5)
setReal(model, "HelloWorld.a", -2.0)
setStopTime(model, 1.0)
-- initialize and simulate
initialize(model)
stepUntil(model, 1.0)
tcur = getCurrentTime(model)
print("Parametrization 2: HelloWorld.x at " .. tcur .. ": " .. getReal(model, "HelloWorld.x"))


terminate(model)

unload(model)

-- Result:
-- Parametrization 1: HelloWorld.x at 1: 0.36603234127323
-- Parametrization 2: HelloWorld.x at 1: 0.066309777947377
-- endResult
