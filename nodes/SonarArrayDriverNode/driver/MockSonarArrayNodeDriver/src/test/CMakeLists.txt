catkin_add_gtest(test_mockSonarArrayNodeDriver test_MockSonarArrayNodeDriver.cpp)
target_link_libraries(test_mockSonarArrayNodeDriver ${catkin_LIBRARIES} ${Boost_LIBRARIES} mockSonarArrayNodeDriver)
add_dependencies(test_mockSonarArrayNodeDriver eros_generate_messages_cpp)
