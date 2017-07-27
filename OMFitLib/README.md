# Tests for the OMFit module C-API bindings

This folder contains tests for the OMFit module that can be executed by cmake/ctest, see CMakeLists.txt, e.g., in the OMFMISimulator build directory do:

```shell
ctest -V
```

Additionally, the tests can be executed as ROOT Cling scripts using the CERN
ROOT Data Analysis Framework, [https://root.cern.ch/](https://root.cern.ch/).
Use the `runRoot.sh` for this purpose (this will start Root and load the required
shared libraries), e.g.:

```shell
./runRoot.sh test_CAPI.c test_cs_HelloWorld_Fit.c
```
