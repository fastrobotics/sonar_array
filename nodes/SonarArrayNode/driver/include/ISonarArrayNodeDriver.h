/**
 * @file ISonarArrayNodeDriver.h
 * @author David Gitz
 * @brief
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros/Logger.h>
#include <eros_diagnostic/Diagnostic.h>
#include <eros_diagnostic/DiagnosticUtility.h>

namespace sonar_array {
class ISonarArrayNodeDriver
{
   public:
    ISonarArrayNodeDriver() {
    }
    virtual ~ISonarArrayNodeDriver(){};
    /**
     * @brief Initialize Sonar Array Node Driver
     *
     * @param logger
     * @return true
     * @return false
     */
    virtual bool init(eros::eros_diagnostic::Diagnostic diagnostic, eros::Logger* logger) = 0;
    virtual bool is_fully_initialized() = 0;

    virtual eros::eros_diagnostic::Diagnostic update(double current_time_sec, double dt) = 0;

    /**
     * @brief Finish and Close Driver
     *
     * @return true
     * @return false
     */
    virtual bool finish() = 0;
    virtual std::string pretty(std::string mode = "") = 0;
};
}  // namespace sonar_array