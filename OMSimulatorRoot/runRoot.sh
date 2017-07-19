#!/bin/sh
# Helper script ensuring that shared libraries are loaded as part of the invocation

# if [ $# -eq 0 ]
#   then
#     echo "runRoot.sh No arguments supplied. Usage:\nrunRoot.sh myExample.C"
#     exit 1
# fi

root -l -e 'gSystem->Load("../../3rdParty/FMIL/install/linux/lib/libfmilib_shared.so"); gSystem->Load("../../install/lib/libOMSimulatorLib.so");' $1

# -l : do not show splash screen
# -q : exit after processing command line macro files
# -e : evaluate any expression as part of the invocation
