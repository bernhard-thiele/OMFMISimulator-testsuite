project(paramest)

set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${FMILibrary_INCLUDEDIR})
link_directories(${FMILibrary_LIBRARYDIR} ${Boost_LIBRARY_DIRS})

# BEGIN CERN ROOT related definitions
# Adapted from https://root.cern.ch/how/integrate-root-my-project-cmake
#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Net)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
ROOT_GENERATE_DICTIONARY(G__Event Event.h LINKDEF EventLinkDef.h)

#---Create a shared library with geneated dictionary
# add_library(Event SHARED Event.cxx G__Event.cxx)
# target_link_libraries(Event ${ROOT_LIBRARIES})

#---Create  a main program using the library
# add_executable(Main MainEvent.cxx)
# target_link_libraries(Main Event)
# END CERN ROOT related definitions

add_executable(exampleErrorGraph exampleErrorGraph.C)
target_link_libraries(exampleErrorGraph ${ROOT_LIBRARIES})
install(TARGETS exampleErrorGraph DESTINATION bin)

add_executable(test_cfunc_HelloWorld test_cfunc_HelloWorld.C)
target_link_libraries(test_cfunc_HelloWorld ${ROOT_LIBRARIES})
install(TARGETS test_cfunc_HelloWorld DESTINATION bin)

add_executable(test_cs_HelloWorld test_cs_HelloWorld.C)
target_link_libraries(test_cs_HelloWorld OMSimulatorLib ${FMILibrary_LIBRARY} ${CMAKE_DL_LIBS} ${Boost_LIBRARIES} ${ROOT_LIBRARIES})
install(TARGETS test_cs_HelloWorld DESTINATION bin)

# Skip executables below (can be added similarly as above if needed)
# test_cs_HelloWorld_withoutReset_SLOW
# test_simbin_HelloWorld

# Copy test FMUs to correct relative installation folder
install(FILES ../FMUs/cs_HelloWorld.fmu DESTINATION FMUs)

# BEGIN CERES related definitions
# Adapted from http://ceres-solver.org/installation.html
# Working with an installed Ceres (make install)
find_package(Ceres REQUIRED)
include_directories(${CERES_INCLUDE_DIRS})

# helloworld from Ceres project
add_executable(exampleCeresHelloWorld exampleCeresHelloWorld.cc)
target_link_libraries(exampleCeresHelloWorld ${CERES_LIBRARIES})
install(TARGETS exampleCeresHelloWorld DESTINATION bin)
# Curve fitting example from Ceres project
add_executable(curve_fitting curve_fitting.cc)
target_link_libraries(curve_fitting ${CERES_LIBRARIES})
install(TARGETS curve_fitting DESTINATION bin)
# END CERES related definitions

add_executable(test_ceres_cfunc_HelloWorld test_ceres_cfunc_HelloWorld.C)
target_link_libraries(test_ceres_cfunc_HelloWorld ${ROOT_LIBRARIES} ${CERES_LIBRARIES})
install(TARGETS test_ceres_cfunc_HelloWorld DESTINATION bin)

add_executable(test_ceres_cs_HelloWorld test_ceres_cs_HelloWorld.C)
target_link_libraries(test_ceres_cs_HelloWorld OMSimulatorLib ${FMILibrary_LIBRARY} ${CMAKE_DL_LIBS} ${Boost_LIBRARIES} ${ROOT_LIBRARIES} ${CERES_LIBRARIES})
install(TARGETS test_ceres_cs_HelloWorld DESTINATION bin)
