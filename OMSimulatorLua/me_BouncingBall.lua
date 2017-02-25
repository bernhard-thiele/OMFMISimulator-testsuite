#!/usr/bin/lua
-- name: me_BouncingBall
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

print("# getVersion")
version = getVersion()
-- print(version)

print("\n# setWorkingDirectory")
setWorkingDirectory(".")

print("\n# loadModel")
fmu = loadModel("../FMUs/me_BouncingBall.fmu")

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
-- GUID: {73c6f0b5-4162-4f6d-86cf-e740bf59af0b}
-- Model identifier for ME: BouncingBall
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
