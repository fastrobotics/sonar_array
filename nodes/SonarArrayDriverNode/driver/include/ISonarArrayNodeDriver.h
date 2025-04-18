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
#include <sensor_msgs/Range.h>

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
    virtual bool init(eros::eros_diagnostic::Diagnostic diagnostic,
                      eros::Logger* logger,
                      std::vector<sensor_msgs::Range> sonars) = 0;
    virtual bool is_fully_initialized() = 0;
    virtual bool set_comm_device(std::string comm_device, int speed) = 0;

    virtual eros::eros_diagnostic::Diagnostic update(double current_time_sec, double dt) = 0;

    /**
     * @brief Finish and Close Driver
     *
     * @return true
     * @return false
     */
    virtual bool finish() = 0;
    virtual std::string pretty(std::string mode = "") = 0;
    virtual std::vector<sensor_msgs::Range> get_sonar_data() = 0;
    virtual std::string pretty(std::vector<sensor_msgs::Range> sonar_data) = 0;
};
}  // namespace sonar_array