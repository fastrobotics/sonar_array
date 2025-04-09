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
    std::vector<eros::eros_diagnostic::Diagnostic> init(
        eros::eros_diagnostic::Diagnostic diagnostic,
        eros::Logger* logger,
        std::vector<sensor_msgs::Range> sonars) override {
        BaseSonarArrayNodeDriver::init(diagnostic, logger, sonars);
        diagnostic =
            diagnostic_manager.update_diagnostic(eros::eros_diagnostic::DiagnosticType::SOFTWARE,
                                                 eros::Level::Type::INFO,
                                                 eros::eros_diagnostic::Message::NOERROR,
                                                 "Tester Fully Initialized.");
        if (diagnostic_manager.get_highest_level() < eros::Level::Type::WARN) {
            fully_initialized = true;
        }
        return diagnostic_manager.get_diagnostics();
    }
    std::vector<eros::eros_diagnostic::Diagnostic> set_comm_device(std::string /* comm_device */,
                                                                   int /* speed */) {
        diagnostic = diagnostic_manager.update_diagnostic(
            eros::eros_diagnostic::DiagnosticType::COMMUNICATIONS,
            eros::Level::Type::INFO,
            eros::eros_diagnostic::Message::NOERROR,
            "Tester Fully Initialized.");
        return diagnostic_manager.get_diagnostics();
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
    EXPECT_LE(eros::eros_diagnostic::DiagnosticManager::get_highest_level(
                  SUT.init(diagnostic, logger, sonars)),
              eros::Level::Type::NOTICE);
    EXPECT_TRUE(SUT.is_fully_initialized());

    delete logger;
}
TEST(BasicTest, FailureModes) {
    {  // Logger not initialized
        eros::Logger* logger = nullptr;
        TesterSonarArrayNodeDriver SUT;
        eros::eros_diagnostic::Diagnostic diagnostic;
        std::vector<sensor_msgs::Range> sonars;
        EXPECT_GE(eros::eros_diagnostic::DiagnosticManager::get_highest_level(
                      SUT.init(diagnostic, logger, sonars)),
                  eros::Level::Type::WARN);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}