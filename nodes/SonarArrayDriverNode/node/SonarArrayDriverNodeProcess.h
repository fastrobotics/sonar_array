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
#include "MockSonarArrayNodeDriver.h"
#include "SonarArrayNodeDriver.h"

namespace sonar_array {
/*! \class SonarArrayDriverNodeProcess SonarArrayDriverNodeProcess.h "SonarArrayDriverNodeProcess.h"
 *  \brief */
class SonarArrayDriverNodeProcess : public eros::BaseNodeProcess
{
   public:
    SonarArrayDriverNodeProcess();
    ~SonarArrayDriverNodeProcess();
    eros::eros_diagnostic::Diagnostic finish_initialization();
    void set_enable_mock(bool v) {
        enable_mock = v;
    }
    void set_sonar_config(std::vector<sensor_msgs::Range> _sonar_config) {
        sonar_config = _sonar_config;
    }
    void set_comm_port(std::string _comm_port) {
        comm_port = _comm_port;
    }
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
    bool enable_mock{false};
    std::vector<sensor_msgs::Range> sonar_config;
    std::string comm_port;
    ISonarArrayNodeDriver* driver;  // Enable during AB#1452
};
}  // namespace sonar_array
