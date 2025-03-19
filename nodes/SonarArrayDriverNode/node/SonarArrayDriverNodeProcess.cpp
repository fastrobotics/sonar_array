#include "SonarArrayDriverNodeProcess.h"

namespace sonar_array {
SonarArrayDriverNodeProcess::SonarArrayDriverNodeProcess() {
}
SonarArrayDriverNodeProcess::~SonarArrayDriverNodeProcess() {
    delete driver;
    delete logger;
}
eros::eros_diagnostic::Diagnostic SonarArrayDriverNodeProcess::finish_initialization() {
    eros::eros_diagnostic::Diagnostic diag = get_root_diagnostic();
    if (enable_mock) {
        logger->log_warn("Enabling Mock Sonary Array Node Driver.");
        driver = new MockSonarArrayNodeDriver();
    }
    else {
        driver = new SonarArrayNodeDriver();
    }

    // Clean up this during AB#1491
    std::vector<sensor_msgs::Range> sonars;
    sonars.resize(1);
    for (std::size_t i = 0; i < sonars.size(); ++i) {
        sonars.at(i).radiation_type = sensor_msgs::Range::ULTRASOUND;
        sonars.at(i).field_of_view = 30.0 * M_PI / 180.0;
        sonars.at(i).min_range = 0.02;  // meters
        sonars.at(i).max_range = 2.0;   // meters
        sonars.at(i).header.frame_id = "sonar_array";
    }
    driver->init(diag, logger, sonars);
    driver->set_comm_device("/dev/ttyUSB0", B115200);

    return diag;
}

void SonarArrayDriverNodeProcess::reset() {
}

eros::eros_diagnostic::Diagnostic SonarArrayDriverNodeProcess::update(double t_dt,
                                                                      double t_ros_time) {
    eros::eros_diagnostic::Diagnostic diag = base_update(t_dt, t_ros_time);
    // Support during AB#1452
    diag = driver->update(t_ros_time, t_dt);
    return diag;
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayDriverNodeProcess::new_commandmsg(
    eros::command msg) {
    (void)msg;
    std::vector<eros::eros_diagnostic::Diagnostic> diag_list;
    logger->log_warn("No Command Messages Supported at this time.");
    return diag_list;
}
std::vector<eros::eros_diagnostic::Diagnostic>
SonarArrayDriverNodeProcess::check_programvariables() {
    std::vector<eros::eros_diagnostic::Diagnostic> diag_list;
    logger->log_warn("No Program Variables Checked.");
    return diag_list;
}
std::string SonarArrayDriverNodeProcess::pretty() {
    std::string str = "Node State: " + eros::Node::NodeStateString(get_nodestate());
    return str;
}
}  // namespace sonar_array