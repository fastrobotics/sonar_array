add_library(sonarArrayNodeProcess SonarArrayNodeProcess.cpp)
target_link_libraries(sonarArrayNodeProcess ${catkin_LIBRARIES} baseNodeProcess sonarArrayNodeDriver )


add_executable(sonar_array_node SonarArrayNode.cpp) 
target_link_libraries(sonar_array_node ${catkin_LIBRARIES} ${Boost_LIBRARIES} sonarArrayNodeProcess baseNode)
add_dependencies(sonar_array_node ${eros_EXPORTED_TARGETS})
add_subdirectory(test)
