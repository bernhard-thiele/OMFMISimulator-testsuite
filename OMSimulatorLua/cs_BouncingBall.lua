#!/usr/bin/lua
-- name: cs_BouncingBall
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

print("# getVersion")
version = getVersion()
-- print(version)

print("\n# setWorkingDirectory")
setWorkingDirectory(".")

print("\n# loadModel")
fmu = loadModel("../FMUs/cs_BouncingBall.fmu")

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
--
-- # setWorkingDirectory
--
-- # loadModel
--
-- # describe
-- FMI version: 2.0
-- Model name: BouncingBall
-- GUID: {b66c08d9-a87a-41ea-aed4-3275f6000fde}
-- Model identifier for CS: BouncingBall
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
