/**
 * @file SonarArrayNodeDriver.h
 * @author David Gitz
 * @brief
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros/Logger.h>
#include <eros_utility/ConvertUtility.h>
#include <eros_utility/PrettyUtility.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "BaseSonarArrayNodeDriver.h"

//! sonar_array Namespace
namespace sonar_array {
/**
 * @brief SonarArrayNodeDriver Class
 * @details
 */
class MockSonarArrayNodeDriver : public BaseSonarArrayNodeDriver
{
   public:
    MockSonarArrayNodeDriver();
    virtual ~MockSonarArrayNodeDriver();
    /**
     * @brief Initialize Sonar Array Node Driver
     *
     * @param logger
     * @return true
     * @return false
     */
    std::vector<eros::eros_diagnostic::Diagnostic> init(
        eros::eros_diagnostic::Diagnostic diagnostic,
        eros::Logger* logger,
        std::vector<sensor_msgs::Range> sonars) override;
    std::vector<eros::eros_diagnostic::Diagnostic> set_comm_device(std::string /* comm_device */,
                                                                   int /* speed */) override {
        diagnostic = diagnostic_manager.update_diagnostic(
            eros::eros_diagnostic::DiagnosticType::COMMUNICATIONS,
            eros::Level::Type::INFO,
            eros::eros_diagnostic::Message::NOERROR,
            "Sonar Array Node Driver Comm Port Fully Initialized.");
        return diagnostic_manager.get_diagnostics();
    }
    std::vector<eros::eros_diagnostic::Diagnostic> update(double current_time_sec,
                                                          double dt) override;

    /**
     * @brief Finish and Close Driver
     *
     * @return true
     * @return false
     */
    bool finish() override;
    std::string pretty(std::string mode = "") override;

   private:
};
}  // namespace sonar_array