# Tests for parameter estimation module

Uses the ROOT scientific software framework. This folder contains
ROOT Cling scripts (C++) that perform the computations. Use the
helper script to ensure that dynamic libraries are loaded into root, e.g.:

```
./runRoot test_cfunc_HelloWorld.C
```

## Dependencies

- ROOT, [https://root.cern.ch/](https://root.cern.ch/)

## Performance

One run in Ubuntu 14.04.5 LTS on my laptop
(Intel(R) Core(TM) i7-4702MQ CPU @ 2.20GHz; SSD hard disk)
gave the following measurements with the interpreted test cases:

| Test case                            | time for fitting (ms) | factor |
| ---------                            | --------------------: | -----  |
| test_cs_HelloWorld.C                 | 4648                  | 1      |
| test_simbin_HelloWorld               | 96438                 | 20.7   |
| test_cs_HelloWorld_withoutReset_SLOW | 350244                | 78.4   |
| test_ceres_cs_HelloWorld.C           | 380                   | 0.08   |
| test_cfunc_HelloWorld.C              | 27                    | 0.006  |
| test_cfunc_HelloWorld.C              | 2                     | 0.0004 |

## Other notes

- https://root.cern.ch/how/integrate-root-my-project-cmake
- http://ceres-solver.org/
  - Using git-hash: 541968497a0cfb34673c17b3f63a1ef183be7de0
