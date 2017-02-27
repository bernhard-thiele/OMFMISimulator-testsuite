#project(simunits)

include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)
#link_directories(${FMILibrary_LIBRARYDIR} ${Boost_LIBRARY_DIRS})

add_executable(test_simunits test_simunits.cpp)

target_link_libraries(test_simunits simunits)

install(TARGETS test_simunits DESTINATION bin)
