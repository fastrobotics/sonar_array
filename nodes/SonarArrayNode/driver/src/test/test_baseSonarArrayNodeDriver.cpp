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
    bool init(eros::eros_diagnostic::Diagnostic diagnostic, eros::Logger* logger) override {
        bool status = BaseSonarArrayNodeDriver::init(diagnostic, logger);
        if (status == true) {
            fully_initialized = true;
            return true;
        }
        return false;
    }
    bool finish() {
        return true;
    }
};
TEST(BasicTest, Test_Initialization) {
    eros::Logger* logger = new eros::Logger("DEBUG", "test_baseSonarArrayNodeDriver");
    TesterSonarArrayNodeDriver SUT;
    eros::eros_diagnostic::Diagnostic diagnostic;
    SUT.init(diagnostic, logger);
    EXPECT_TRUE(SUT.is_fully_initialized());

    delete logger;
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}