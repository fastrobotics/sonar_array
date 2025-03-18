/**
 * @file SonarNodeProcess.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-12
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros/BaseNodeProcess.h>
#include <eros_diagnostic/Diagnostic.h>

#include "ISonarArrayNodeDriver.h"
#include "SonarArrayNodeDriver.h"

namespace sonar_array {
/*! \class SonarArrayNodeProcess SonarArrayNodeProcess.h "SonarArrayNodeProcess.h"
 *  \brief */
class SonarArrayNodeProcess : public eros::BaseNodeProcess
{
   public:
    SonarArrayNodeProcess();
    ~SonarArrayNodeProcess();
    eros::eros_diagnostic::Diagnostic finish_initialization();
    void reset();
    eros::eros_diagnostic::Diagnostic update(double t_dt, double t_ros_time);
    std::vector<eros::eros_diagnostic::Diagnostic> new_commandmsg(eros::command msg);
    std::vector<eros::eros_diagnostic::Diagnostic> check_programvariables();
    void cleanup() {
        base_cleanup();
        return;
    }
    std::vector<sensor_msgs::Range> get_sonar_data() {
        if (driver == nullptr) {
            std::vector<sensor_msgs::Range> empty;
            return empty;
        }
        else {
            return driver->get_sonar_data();
        }
    }
    std::string pretty() override;

   private:
    ISonarArrayNodeDriver* driver;  // Enable during AB#1452
};
}  // namespace sonar_array
