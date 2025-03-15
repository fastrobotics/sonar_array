include_directories(
    driver/include/
    driver/SonarArrayNodeDriver/include/
    driver/MockSonarArrayNodeDriver/include/
    ${catkin_INCLUDE_DIRS}
)
add_subdirectory(driver)
add_subdirectory(node)