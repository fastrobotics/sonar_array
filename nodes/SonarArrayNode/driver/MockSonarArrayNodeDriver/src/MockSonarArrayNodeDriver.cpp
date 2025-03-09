#include "MockSonarArrayNodeDriver.h"
namespace sonar_array {
MockSonarArrayNodeDriver::MockSonarArrayNodeDriver() {
}
MockSonarArrayNodeDriver::~MockSonarArrayNodeDriver() {
    finish();
}
bool MockSonarArrayNodeDriver::finish() {
    return true;
}
bool MockSonarArrayNodeDriver::init(eros::eros_diagnostic::Diagnostic _diagnostic,
                                    eros::Logger* _logger) {
    return BaseSonarArrayNodeDriver::init(_diagnostic, _logger);
}
eros::eros_diagnostic::Diagnostic MockSonarArrayNodeDriver::update(double current_time_sec,
                                                                   double dt) {
    diagnostic = BaseSonarArrayNodeDriver::update(current_time_sec, dt);
    return diagnostic;
}
std::string MockSonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Mock Sonar Array Node Driver";
    str += BaseSonarArrayNodeDriver::pretty(mode);
    return str;
}
}  // namespace sonar_array