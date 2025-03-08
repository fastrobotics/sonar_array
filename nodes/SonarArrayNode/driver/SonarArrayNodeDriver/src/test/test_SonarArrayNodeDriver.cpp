/*! \file test_SonarArrayNodeDriver.cpp
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include "../../include/SonarArrayNodeDriver.h"
using namespace eros;
using namespace sonar_array;
TEST(BasicTest, TestDefinitions) {
    EXPECT_TRUE(true);
}
TEST(BasicTest, TestOperation) {
    Logger* logger = new Logger("DEBUG", "UnitTestSonarArrayNodeDriver");
    SonarArrayNodeDriver SUT;
    SUT.init(logger);

    double timeToRun = 10.0;
    double dt = 0.1;
    double timer = 0.0;
    while (timer <= timeToRun) {
        EXPECT_TRUE(SUT.update(dt));

        logger->log_debug(SUT.pretty());
        timer += dt;
    }

    // delete logger;
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
