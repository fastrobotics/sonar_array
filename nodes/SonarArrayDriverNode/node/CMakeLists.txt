add_library(sonarArrayDriverNodeProcess SonarArrayDriverNodeProcess.cpp)
target_link_libraries(sonarArrayDriverNodeProcess ${catkin_LIBRARIES} baseNodeProcess sonarArrayNodeDriver mockSonarArrayNodeDriver)


add_executable(sonar_array_driver_node SonarArrayDriverNode.cpp) 
target_link_libraries(sonar_array_driver_node ${catkin_LIBRARIES} ${Boost_LIBRARIES} sonarArrayDriverNodeProcess baseNode)
add_dependencies(sonar_array_driver_node ${eros_EXPORTED_TARGETS})
add_subdirectory(test)
