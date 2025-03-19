/*! \file test_baseSonarArrayNodeDriver.cpp
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include "BaseSonarArrayNodeDriver.h"
using namespace sonar_array;
class TesterSonarArrayNodeDriver : public BaseSonarArrayNodeDriver
{
   public:
    TesterSonarArrayNodeDriver() {
    }
    virtual ~TesterSonarArrayNodeDriver() {
        finish();
    }
    bool init(eros::eros_diagnostic::Diagnostic diagnostic,
              eros::Logger* logger,
              std::vector<sensor_msgs::Range> sonars) override {
        bool status = BaseSonarArrayNodeDriver::init(diagnostic, logger, sonars);
        if (status == true) {
            fully_initialized = true;
            return true;
        }
        return false;
    }
    bool set_comm_device(std::string /* comm_device */, int /* speed */) {
        return true;
    }
    bool finish() {
        return true;
    }
};
TEST(BasicTest, Test_Initialization) {
    eros::Logger* logger = new eros::Logger("DEBUG", "test_baseSonarArrayNodeDriver");
    TesterSonarArrayNodeDriver SUT;
    eros::eros_diagnostic::Diagnostic diagnostic;
    std::vector<sensor_msgs::Range> sonars;
    sonars.resize(1);
    EXPECT_TRUE(SUT.init(diagnostic, logger, sonars));
    EXPECT_TRUE(SUT.is_fully_initialized());

    delete logger;
}
TEST(BasicTest, FailureModes) {
    {  // Logger not initialized
        eros::Logger* logger = nullptr;
        TesterSonarArrayNodeDriver SUT;
        eros::eros_diagnostic::Diagnostic diagnostic;
        std::vector<sensor_msgs::Range> sonars;
        EXPECT_FALSE(SUT.init(diagnostic, logger, sonars));
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}