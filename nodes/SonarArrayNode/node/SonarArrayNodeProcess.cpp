#include "SonarArrayNodeProcess.h"

namespace sonar_array {
SonarArrayNodeProcess::SonarArrayNodeProcess() {
}
SonarArrayNodeProcess::~SonarArrayNodeProcess() {
    delete logger;
}
eros::eros_diagnostic::Diagnostic SonarArrayNodeProcess::finish_initialization() {
    eros::eros_diagnostic::Diagnostic diag = get_root_diagnostic();
    return diag;
}

void SonarArrayNodeProcess::reset() {
}

eros::eros_diagnostic::Diagnostic SonarArrayNodeProcess::update(double t_dt, double t_ros_time) {
    eros::eros_diagnostic::Diagnostic diag = base_update(t_dt, t_ros_time);
    return diag;
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayNodeProcess::new_commandmsg(
    eros::command msg) {
    (void)msg;
    std::vector<eros::eros_diagnostic::Diagnostic> diag_list;
    logger->log_warn("No Command Messages Supported at this time.");
    return diag_list;
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayNodeProcess::check_programvariables() {
    std::vector<eros::eros_diagnostic::Diagnostic> diag_list;
    logger->log_warn("No Program Variables Checked.");
    return diag_list;
}
std::string SonarArrayNodeProcess::pretty() {
    std::string str = "Node State: " + eros::Node::NodeStateString(get_nodestate());
    return str;
}
}  // namespace sonar_array