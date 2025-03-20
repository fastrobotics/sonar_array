/*! \file test_MockSonarArrayNodeDriver.cpp
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include "../../include/MockSonarArrayNodeDriver.h"
using namespace eros;
using namespace sonar_array;
TEST(BasicTest, TestDefinitions) {
    EXPECT_TRUE(true);
}
TEST(BasicTest, TestOperation) {
    Logger* logger = new Logger("DEBUG", "UnitTestMockSonarArrayNodeDriver");
    ISonarArrayNodeDriver* SUT = new MockSonarArrayNodeDriver();
    eros::eros_diagnostic::Diagnostic diagnostic;
    std::vector<sensor_msgs::Range> sonars;
    sonars.resize(10);
    SUT->init(diagnostic, logger, sonars);

    double timeToRun = 10.0;
    double dt = 0.1;
    double timer = 0.0;
    while (timer <= timeToRun) {
        auto diagnostic = SUT->update(timer, dt);
        EXPECT_TRUE(diagnostic.level <= eros::Level::Type::NOTICE);
        EXPECT_GT(SUT->get_sonar_data().size(), 0);

        // logger->log_debug(SUT.pretty());
        timer += dt;
    }

    // delete logger;
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
