#project(simunits)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${FMILibrary_INCLUDEDIR} ${Mach7Library_INCLUDEDIR})
link_directories(${FMILibrary_LIBRARYDIR} ${Boost_LIBRARY_DIRS})

# add_executable(test_core test_core.cpp)
# target_link_libraries(test_core simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARY})
# install(TARGETS test_core DESTINATION bin)

add_executable(test_simunits_fmi20 test_simunits_fmi20.cpp)
target_link_libraries(test_simunits_fmi20 simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARY})
install(TARGETS test_simunits_fmi20 DESTINATION bin)

add_executable(test_simunits_fmi20system test_simunits_fmi20system.cpp)
target_link_libraries(test_simunits_fmi20system simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARY})
install(TARGETS test_simunits_fmi20system DESTINATION bin)

add_executable(test_simunits_factory test_simunits_factory.cpp)
target_link_libraries(test_simunits_factory simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARY})
install(TARGETS test_simunits_factory DESTINATION bin)

add_executable(test_mach7 test_mach7.cpp)
install(TARGETS test_mach7 DESTINATION bin)

add_executable(numbers numbers.cpp)
install(TARGETS numbers DESTINATION bin)

add_executable(test_ADT test_ADT.cpp)
install(TARGETS test_ADT DESTINATION bin)
