catkin_add_gtest(test_sonarArrayDriverNodeProcess test_SonarArrayDriverNodeProcess.cpp)
target_link_libraries(test_sonarArrayDriverNodeProcess ${catkin_LIBRARIES} ${Boost_LIBRARIES} logger sonarArrayDriverNodeProcess)
add_dependencies(test_sonarArrayDriverNodeProcess eros_generate_messages_cpp)

add_rostest_gtest(test_sonarArrayDriverNode
    test_SonarArrayDriverNode.test
    test_SonarArrayDriverNode.cpp
)
add_dependencies(test_sonarArrayDriverNode sonar_array_driver_node)
target_link_libraries(test_sonarArrayDriverNode ${catkin_LIBRARIES}  ${Boost_LIBRARIES} ${GTEST_LIBRARIES} logger)
