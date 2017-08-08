project(OMFitLib)

set(CMAKE_VERBOSE_MAKEFILE ON)
# For testing use either
# CTEST_OUTPUT_ON_FAILURE=1 make test
# for showing any output from a test program whenever a test fails
# or
# ctest -V
# for showing the stdout output for all test cases, alternatively, for a specific test,
# make test ARGS="-V -R some-specific-test"


include_directories(${CERES_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${FMILibrary_INCLUDEDIR})
link_directories(${FMILibrary_LIBRARYDIR} ${Boost_LIBRARY_DIRS})

set(OMFITTEST_LIBRARIES OMFit OMSimulatorLib ${FMILibrary_LIBRARY} sundials_cvode sundials_nvecserial ${CMAKE_DL_LIBS} ${Boost_LIBRARIES} ${CERES_LIBRARIES})

add_executable(test_cs_HelloWorld_Fit test_cs_HelloWorld_Fit.c)
target_link_libraries(test_cs_HelloWorld_Fit ${OMFITTEST_LIBRARIES})
add_test(NAME test_cs_HelloWorld_Fit
  COMMAND test_cs_HelloWorld_Fit
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_cs_Lin2DimODE_Fit test_cs_Lin2DimODE_Fit.cpp)
target_link_libraries(test_cs_Lin2DimODE_Fit ${OMFITTEST_LIBRARIES})
add_test(NAME test_cs_Lin2DimODE_Fit
  COMMAND test_cs_Lin2DimODE_Fit
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
