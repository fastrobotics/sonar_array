catkin_add_gtest(test_sonarArrayNodeProcess test_SonarArrayNodeProcess.cpp)
target_link_libraries(test_sonarArrayNodeProcess ${catkin_LIBRARIES} ${Boost_LIBRARIES} logger sonarArrayNodeProcess)
add_dependencies(test_sonarArrayNodeProcess eros_generate_messages_cpp)

add_rostest_gtest(test_sonarArrayNode
    test_SonarArrayNode.test
    test_SonarArrayNode.cpp
)
add_dependencies(test_sonarArrayNode sonar_array_node)
target_link_libraries(test_sonarArrayNode ${catkin_LIBRARIES}  ${Boost_LIBRARIES} ${GTEST_LIBRARIES} logger)
