#include "SonarArrayNodeDriver.h"
namespace sonar_array {
SonarArrayNodeDriver::SonarArrayNodeDriver() {
}
SonarArrayNodeDriver::~SonarArrayNodeDriver() {
    finish();
}
bool SonarArrayNodeDriver::finish() {
    return true;
}
bool SonarArrayNodeDriver::init(eros::Logger* _logger) {
    logger = _logger;
    return true;
}
bool SonarArrayNodeDriver::update(double dt) {
    return true;
}
std::string SonarArrayNodeDriver::pretty() {
    std::string str = "Sonar Array Node Driver";
    return str;
}
}  // namespace sonar_array