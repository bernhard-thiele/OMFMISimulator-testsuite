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
model = newModel()

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

setStartTime(model, 0.0)
setStopTime(model, 10.0)
setTolerance(model, 1e-5)

exportXML(model, "ImportExport.xml")

model2 = loadModel("ImportExport.xml")
describe(model2)

unload(model)
unload(model2)

-- Result:
-- # FMU instances
-- adder
--   - FMI 2.0 ME
--   - path: ../FMUs/me_adder1.fmu
--   - GUID: {bd121558-6b16-4944-819d-dd5fc0b9b8ea}
--   - tool: OpenModelica Compiler OMCompiler v1.12.0-dev.395+gdeeabde
--   - input interface:
--     - input x1
--     - input x2
--   - output interface:
--     - output y
-- sourceA
--   - FMI 2.0 ME
--   - path: ../FMUs/me_source1.fmu
--   - GUID: {a31d622a-f33e-4172-9c76-96665d8d1b60}
--   - tool: OpenModelica Compiler OMCompiler v1.12.0-dev.395+gdeeabde
--   - input interface:
--   - output interface:
--     - output y
-- sourceB
--   - FMI 2.0 ME
--   - path: ../FMUs/me_source1.fmu
--   - GUID: {a31d622a-f33e-4172-9c76-96665d8d1b60}
--   - tool: OpenModelica Compiler OMCompiler v1.12.0-dev.395+gdeeabde
--   - input interface:
--   - output interface:
--     - output y
--
-- # Simulation settings
--   - start time: 0
--   - stop time: 10
--   - tolerance: 1e-05
--   - communication interval: <undefined>
--   - result file: <no result file>
--
-- # Composite structure
-- ## Initialization
-- sourceB.y -> adder.x2
-- sourceA.y -> adder.x1
--
-- ## Simulation
-- sourceB.y -> adder.x2
-- sourceA.y -> adder.x1
--
-- endResult
