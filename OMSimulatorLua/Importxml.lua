#!/usr/bin/lua
-- name: test2
-- status: correct

if os.getenv("OS") == "Windows_NT" then
  package.cpath = package.cpath .. ';../../install/lib/?.dll'
else
  package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
end
require("OMSimulatorLua")

version = getVersion()
-- print(version)

setTempDirectory(".")
model = loadModel('ConnectedFmu.xml')

setReal(model, "sourceA.A", 0.5)
setReal(model, "sourceA.omega", 2.0)

setStopTime(model, 10.0)
initialize(model)
stepUntil(model, 10.0)
tcur = getCurrentTime(model)
print("adder1.y at " .. tcur .. ": " .. getReal(model, "adder1.y"))
print("adder2.y at " .. tcur .. ": " .. getReal(model, "adder2.y"))


-- Result:
-- adder1.y at 10.1: -0.050699025021762
-- adder2.y at 10.1: -0.48303321299316
-- endResult
