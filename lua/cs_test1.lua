#!/usr/bin/lua
package.cpath = package.cpath .. ';../../install/lib/libluaOMSimulator.so'
require("libluaOMSimulator")

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
