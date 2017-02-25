#!/usr/bin/lua
-- name: me_test1
-- status: correct

package.cpath = package.cpath .. ';../../install/lib/libOMSimulatorLua.so'
require("libOMSimulatorLua")

print("# getVersion")
version = getVersion()
-- print(version)

print("\n# setWorkingDirectory")
setWorkingDirectory(".")

print("\n# loadModel")
fmu = loadModel("../FMUs/me_test1.fmu")

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
-- Model name: test1
-- GUID: {ca6102fd-e542-45b3-8990-6feac45dc944}
-- Model identifier for ME: test1
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
