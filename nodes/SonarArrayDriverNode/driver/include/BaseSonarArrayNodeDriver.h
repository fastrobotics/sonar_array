/**
 * @file BaseSonarArrayNodeDriver.h
 * @author David Gitz
 * @brief
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros_utility/ConvertUtility.h>
#include <eros_utility/PrettyUtility.h>

#include "ISonarArrayNodeDriver.h"
namespace sonar_array {

class BaseSonarArrayNodeDriver : public ISonarArrayNodeDriver
{
   public:
    BaseSonarArrayNodeDriver() {
    }
    virtual ~BaseSonarArrayNodeDriver() {
    }
    std::vector<eros::eros_diagnostic::Diagnostic> init(
        eros::eros_diagnostic::Diagnostic diagnostic,
        eros::Logger* logger,
        std::vector<sensor_msgs::Range> sonars);
    bool is_fully_initialized() {
        return fully_initialized;
    }

    std::vector<eros::eros_diagnostic::Diagnostic> update(double current_time_sec, double dt);

    std::string pretty(std::string mode);
    std::vector<sensor_msgs::Range> get_sonar_data() {
        return sonars;
    }
    double get_runtime() {
        return run_time;
    }
    std::string pretty(std::vector<sensor_msgs::Range> sonar_data);

   protected:
    eros::eros_diagnostic::Diagnostic diagnostic;
    eros::Logger* logger;
    bool fully_initialized{false};
    std::vector<sensor_msgs::Range> sonars;

   private:
    double prev_current_time_sec{-1.0};
    double run_time{0.0};
};
}  // namespace sonar_array