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
-- GUID: {20db05bd-be73-4960-aaa8-ee4be1af214a}
-- Model identifier for ME: me_test1
--
-- # setStopTime
--
-- # setTolerance
--
-- # simulate
--
-- # unload
-- endResult
