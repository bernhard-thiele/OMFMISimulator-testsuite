#project(simunits)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src ${FMILibrary_INCLUDEDIR})
link_directories(${FMILibrary_LIBRARYDIR} ${Boost_LIBRARY_DIRS})

# add_executable(test_simunits test_simunits.cpp)
# target_link_libraries(test_simunits simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARYDIR})
# install(TARGETS test_simunits DESTINATION bin)


add_executable(test_simunits_fmi20 test_simunits_fmi20.cpp)
target_link_libraries(test_simunits_fmi20 simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARYDIR})
install(TARGETS test_simunits_fmi20 DESTINATION bin)

add_executable(test_simunits_system test_simunits_system.cpp)
target_link_libraries(test_simunits_system simunits OMSimulatorLib ${CMAKE_DL_LIBS} ${FMILibrary_LIBRARYDIR})
install(TARGETS test_simunits_system DESTINATION bin)
