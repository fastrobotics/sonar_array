add_executable(exec_sonararray_node_driver exec_SonarArrayNodeDriver.cpp) 
target_link_libraries(exec_sonararray_node_driver ${catkin_LIBRARIES} sonarArrayNodeDriver )
install(TARGETS exec_sonararray_node_driver
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_GLOBAL_BIN_DESTINATION})
