add_library(sonarArrayBoardPacketParser SonarArrayBoardPacketParser.cpp)

add_library(sonarArrayNodeDriver SonarArrayNodeDriver.cpp)
target_link_libraries(sonarArrayNodeDriver ${catkin_LIBRARIES} baseSonarArrayNodeDriver sonarArrayBoardPacketParser)
add_subdirectory(test)