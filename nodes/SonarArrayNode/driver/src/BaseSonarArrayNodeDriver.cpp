#include "BaseSonarArrayNodeDriver.h"
namespace sonar_array {
bool BaseSonarArrayNodeDriver::init(eros::eros_diagnostic::Diagnostic _diagnostic,
                                    eros::Logger* _logger,
                                    std::vector<sensor_msgs::Range> _sonars) {
    diagnostic = _diagnostic;
    if (_logger == nullptr) {
        return false;
    }
    logger = _logger;
    if (_sonars.size() == 0) {
        logger->log_error("Sonar Count is 0!");
        return false;
    }
    sonars = _sonars;

    return true;
}
eros::eros_diagnostic::Diagnostic BaseSonarArrayNodeDriver::update(double current_time_sec,
                                                                   double dt) {
    auto diag = diagnostic;
    if (prev_current_time_sec < 0) {
        prev_current_time_sec = current_time_sec;
        diag.type = eros::eros_diagnostic::DiagnosticType::SOFTWARE;
        diag.level = eros::Level::Type::INFO;
        diag.message = eros::eros_diagnostic::Message::INITIALIZING;
        diag.description = "First Run";
        return diag;
    }
    double elap_time = current_time_sec - prev_current_time_sec;

    run_time += elap_time;
    logger->log_debug(std::to_string(elap_time) + "," + std::to_string(dt));
    prev_current_time_sec = current_time_sec;
    // NO Practical way to Unit Test this
    // GCOVR_EXCL_START
    if (elap_time > (2.0 * dt)) {
        diag.type = eros::eros_diagnostic::DiagnosticType::COMMUNICATIONS;
        diag.level = eros::Level::Type::WARN;
        diag.message = eros::eros_diagnostic::Message::DROPPING_PACKETS;
        diag.description = "Expected Update Time: " + std::to_string(dt) +
                           " Actual Time: " + std::to_string(elap_time);
        return diag;
    }
    // GCOVR_EXCL_STOP
    diag.type = eros::eros_diagnostic::DiagnosticType::SOFTWARE;
    diag.level = eros::Level::Type::INFO;
    diag.message = eros::eros_diagnostic::Message::NOERROR;
    diag.description = "";
    return diag;
}

std::string BaseSonarArrayNodeDriver::pretty(std::string mode) {
    std::string str;
    if (mode == "") {
        str += pretty("simple");
        str += "\nRuntime: " + std::to_string(run_time) + " (sec).\n";
    }
    else if (mode == "simple") {
        str += "\tInitialized: " + std::to_string(fully_initialized) + "\n";
        str += eros::eros_diagnostic::DiagnosticUtility::pretty("\t", diagnostic, false);
    }
    return str;
}

}  // namespace sonar_array