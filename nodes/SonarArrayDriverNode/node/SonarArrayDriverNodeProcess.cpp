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
    std::vector<sensor_msgs::Range> sonars;

    if (enable_mock) {
        logger->log_warn("Enabling Mock Sonary Array Node Driver.");
        driver = new MockSonarArrayNodeDriver();
    }
    else {
        driver = new SonarArrayNodeDriver();
    }
    driver->init(diag, logger, sonar_config);
    if (driver->set_comm_device(comm_port, B115200) == false) {
        diag = update_diagnostic(eros::eros_diagnostic::DiagnosticType::COMMUNICATIONS,
                                 eros::Level::Type::ERROR,
                                 eros::eros_diagnostic::Message::INITIALIZING_ERROR,
                                 "Unable to Initialize Comm Port: " + comm_port);
        return diag;
    }

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