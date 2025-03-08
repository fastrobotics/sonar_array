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
std::string SonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Sonar Array Node Driver";
    str += " Comm Device: " + comm_device_ + "\n";
    str += BaseSonarArrayNodeDriver::pretty(mode);
    return str;
}
bool SonarArrayNodeDriver::set_comm_device(std::string comm_device) {
    comm_device_ = comm_device;
    fd = open(comm_device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        logger->log_error("Error Opening: " + comm_device + " Exception: " + strerror(errno));
        return false;
    }
    fully_initialized = true;
    return true;
}
}  // namespace sonar_array