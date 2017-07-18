#!/usr/bin/lua
-- name: cs_BouncingBall
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

instantiateFMU(model, "../FMUs/cs_BouncingBall.fmu", "BouncingBall")
describe(model)

setStopTime(model, 2.1)
setTolerance(model, 1e-5)

initialize(model)
simulate(model)
terminate(model)

unload(model)

-- Result:
-- # FMU instances
-- BouncingBall
--   - FMI 2.0 CS
--   - path: ../FMUs/cs_BouncingBall.fmu
--   - GUID: {ed0c3e8c-c48f-4995-b80b-eb1d54c9737b}
--   - tool: OpenModelica Compiler OMCompiler v1.12.0-dev.395+gdeeabde
--   - input interface:
--   - output interface:
--
-- # Simulation settings
--   - start time: <undefined>
--   - stop time: <undefined>
--   - tolerance: <undefined>
--   - communication interval: <undefined>
--   - result file: <no result file>
--
-- # Composite structure
-- ## Initialization
--
-- ## Simulation
--
-- endResult
