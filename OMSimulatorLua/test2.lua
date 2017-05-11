#!/usr/bin/lua
-- name: test2
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
--os.execute("dot -Tpdf test_outputsGraph.dot > test_outputsGraph.pdf")

print("adder1.y at 10: " .. getReal(model, "adder1.y"))
print("adder2.y at 10: " .. getReal(model, "adder2.y"))

terminate(model)

unload(model)

-- Result:
-- adder1.y at 10: -0.050699025021762
-- adder2.y at 10: -0.48303321299316
-- endResult
