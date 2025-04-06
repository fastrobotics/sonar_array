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
    auto diag_list = driver->init(diag, logger, sonar_config);
    for (auto driver_diag : diag_list) { update_diagnostic(driver_diag); }
    if (eros::eros_diagnostic::DiagnosticManager::get_highest_level(
            driver->set_comm_device(comm_port, B115200)) >= eros::Level::Type::ERROR) {
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
    auto diag_list = driver->update(t_ros_time, t_dt);
    for (auto driver_diag : diag_list) { update_diagnostic(driver_diag); }
    if (get_runtime() > 10.0) {
        if (driver->get_good_packet_count() == 0) {
            diag = update_diagnostic(eros::eros_diagnostic::DiagnosticType::SENSORS,
                                     eros::Level::Type::ERROR,
                                     eros::eros_diagnostic::Message::NODATA,
                                     "Never received any sonar data.");
        }
    }
    return diag;
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayDriverNodeProcess::new_commandmsg(
    eros::command msg) {
    std::vector<eros::eros_diagnostic::Diagnostic> diag_list = base_new_commandmsg(msg);
    if (diag_list.size() == 0) {
        // No currently supported commands.
    }
    else {
        for (auto diag : diag_list) {
            if (diag.level >= eros::Level::Type::INFO) {
                diagnostic_manager.update_diagnostic(diag);
            }
        }
    }
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