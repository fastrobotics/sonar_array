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
bool MockSonarArrayNodeDriver::init(eros::Logger* _logger) {
    return BaseSonarArrayNodeDriver::init(_logger);
}
bool MockSonarArrayNodeDriver::update(double current_time_sec, double dt) {
    bool status = BaseSonarArrayNodeDriver::update(current_time_sec, dt);
    return status;
}
std::string MockSonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Mock Sonar Array Node Driver";
    str += BaseSonarArrayNodeDriver::pretty(mode);
    return str;
}
}  // namespace sonar_array