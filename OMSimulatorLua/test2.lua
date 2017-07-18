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

model = newModel()
setTempDirectory(".")

-- instantiate FMUs
instantiateFMU(model, "../FMUs/me_source1.fmu", "sourceA")
instantiateFMU(model, "../FMUs/me_source1.fmu", "sourceB")
instantiateFMU(model, "../FMUs/me_adder1.fmu", "adder1")
instantiateFMU(model, "../FMUs/me_adder1.fmu", "adder2")

-- add connections
addConnection(model, "sourceA.y", "adder1.x1")
addConnection(model, "sourceB.y", "adder1.x2")
addConnection(model, "adder1.y", "adder2.x1")
addConnection(model, "sourceB.y", "adder2.x2")

-- set parameter
setReal(model, "sourceA.A", 0.5)
setReal(model, "sourceA.omega", 2.0)

setStopTime(model, 10.0)

initialize(model)
stepUntil(model, 10.0)
--exportDependencyGraph(model, "test")
--os.execute("gvpr -c \"N[$.degree==0]{delete(root, $)}\" test_simulation.dot | dot -Tpdf -o test_simulation.pdf")
--os.execute("gvpr -c \"N[$.degree==0]{delete(root, $)}\" test_initialization.dot | dot -Tpdf -o test_initialization.pdf")

tcur = getCurrentTime(model)
print("adder1.y at " .. tcur .. ": " .. getReal(model, "adder1.y"))
print("adder2.y at " .. tcur .. ": " .. getReal(model, "adder2.y"))

terminate(model)

unload(model)

-- Result:
-- adder1.y at 10: -0.087548485525547
-- adder2.y at 10: -0.59472013591111
-- endResult
