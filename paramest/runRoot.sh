#!/bin/sh
# Helper script ensuring that shared libraries are loaded as part of the invocation

# if [ $# -eq 0 ]
#   then
#     echo "runRoot.sh No arguments supplied. Usage:\nrunRoot.sh myExample.C"
#     exit 1
# fi

# OMSimulator only
# root -l -e 'gSystem->Load("../../3rdParty/FMIL/install/linux/lib/libfmilib_shared.so"); gSystem->Load("../../install/lib/libOMSimulatorLib.so");' $1

# OMSimulator and Ceres
root -l -e 'gSystem->Load("../../3rdParty/FMIL/install/linux/lib/libfmilib_shared.so"); gSystem->Load("../../install/lib/libOMSimulatorLib.so"); gSystem->Load("/usr/local/lib/libceres.so"); gROOT->ProcessLine(".include /usr/include/eigen3");' $1
# NOTE: gSystem->AddIncludePath(" -I/usr/include/eigen3 "); did not work to add the include path, although says so in the docs
# https://root.cern.ch/root/htmldoc/guides/users-guide/Cling.html


# -l : do not show splash screen
# -q : exit after processing command line macro files
# -e : evaluate any expression as part of the invocation
