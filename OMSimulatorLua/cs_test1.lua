#!/usr/bin/lua
-- name: cs_test1
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

print("# getVersion")
version = getVersion()
print(version)

print("\n# setWorkingDirectory")
setWorkingDirectory(".")

print("\n# loadModel")
fmu = loadModel("../FMUs/cs_test1.fmu")

print("\n# describe")
describe(fmu)

print("\n# setStopTime")
setStopTime(2.1)

print("\n# setTolerance")
setTolerance(1e-5)

print("\n# simulate")
simulate(fmu)

print("\n# unload")
unload(fmu)

-- Result:
-- # getVersion
-- OMSimulator v0.0.0-33-gd19ec16
--
-- # setWorkingDirectory
--
-- # loadModel
--
-- # describe
-- FMI version: 2.0
-- Model name: test1
-- GUID: {d8c3f2b4-f180-4ffd-a32c-cdd07602b7bc}
-- Model identifier for CS: test1
--
-- # setStopTime
--
-- # setTolerance
--
-- # simulate
--
-- # unload
-- Logging information has been saved to "omsllog.txt"
-- endResult
