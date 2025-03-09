#include "BaseSonarArrayNodeDriver.h"
namespace sonar_array {
bool BaseSonarArrayNodeDriver::init(eros::Logger* _logger) {
    if (_logger != nullptr) {
        logger = _logger;
        return true;
    }
    return false;
}
bool BaseSonarArrayNodeDriver::update(double current_time_sec, double dt) {
    if (prev_current_time_sec < 0) {
        prev_current_time_sec = current_time_sec;
        return true;
    }
    double elap_time = current_time_sec - prev_current_time_sec;
    if (elap_time > (2.0 * dt)) {
        logger->log_warn("Not keeping up!");
    }
    run_time += elap_time;
    logger->log_debug(std::to_string(elap_time) + "," + std::to_string(dt));
    prev_current_time_sec = current_time_sec;
    return true;
}

std::string BaseSonarArrayNodeDriver::pretty(std::string mode) {
    std::string str;
    if (mode == "") {
        str += pretty("simple");
        str += "\nRuntime: " + std::to_string(run_time) + " (sec).\n";
    }
    else if (mode == "simple") {
        str += "\tInitialized: " + std::to_string(fully_initialized) + "\n";
    }
    return str;
}

}  // namespace sonar_array