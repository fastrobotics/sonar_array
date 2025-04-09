#include "MockSonarArrayNodeDriver.h"
using namespace eros::eros_diagnostic;
namespace sonar_array {
MockSonarArrayNodeDriver::MockSonarArrayNodeDriver() {
}
MockSonarArrayNodeDriver::~MockSonarArrayNodeDriver() {
    finish();
}
bool MockSonarArrayNodeDriver::finish() {
    return true;
}
std::vector<eros::eros_diagnostic::Diagnostic> MockSonarArrayNodeDriver::init(
    eros::eros_diagnostic::Diagnostic _diagnostic,
    eros::Logger* _logger,
    std::vector<sensor_msgs::Range> _sonars) {
    return BaseSonarArrayNodeDriver::init(_diagnostic, _logger, _sonars);
}
std::vector<eros::eros_diagnostic::Diagnostic> MockSonarArrayNodeDriver::update(
    double current_time_sec, double dt) {
    BaseSonarArrayNodeDriver::update(current_time_sec, dt);
    for (std::size_t i = 0; i < sonars.size(); ++i) {
        sonars.at(i).range = sonars.at(i).range += 0.001;
        if (sonars.at(i).range > 2.0) {
            sonars.at(i).range = 0.0;
        }
    }
    diagnostic = diagnostic_manager.update_diagnostic(
        DiagnosticType::SOFTWARE, eros::Level::Type::INFO, Message::NOERROR, "Mock Driver Ok");
    return diagnostic_manager.get_diagnostics();
}
std::string MockSonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Mock Sonar Array Node Driver";
    str += BaseSonarArrayNodeDriver::pretty(mode);
    return str;
}
}  // namespace sonar_array