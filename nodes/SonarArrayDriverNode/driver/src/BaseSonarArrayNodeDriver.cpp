#include "BaseSonarArrayNodeDriver.h"
using namespace eros::eros_diagnostic;
namespace sonar_array {
std::vector<Diagnostic> BaseSonarArrayNodeDriver::init(Diagnostic _diagnostic,
                                                       eros::Logger* _logger,
                                                       std::vector<sensor_msgs::Range> _sonars) {
    diagnostic = _diagnostic;
    diagnostic_manager.initialize(diagnostic);
    std::vector<DiagnosticType> diagnostic_types;
    diagnostic_types.push_back(eros::eros_diagnostic::DiagnosticType::SOFTWARE);
    diagnostic_types.push_back(eros::eros_diagnostic::DiagnosticType::DATA_STORAGE);
    diagnostic_types.push_back(eros::eros_diagnostic::DiagnosticType::SYSTEM_RESOURCE);
    diagnostic_types.push_back(eros::eros_diagnostic::DiagnosticType::COMMUNICATIONS);
    diagnostic_types.push_back(eros::eros_diagnostic::DiagnosticType::SENSORS);
    diagnostic_manager.enable_diagnostics(diagnostic_types);
    if (_logger == nullptr) {
        diagnostic = diagnostic_manager.update_diagnostic(DiagnosticType::SOFTWARE,
                                                          eros::Level::Type::ERROR,
                                                          Message::INITIALIZING_ERROR,
                                                          "Logger Undefined!");

        return diagnostic_manager.get_diagnostics();
    }
    logger = _logger;
    if (_sonars.size() == 0) {
        diagnostic = diagnostic_manager.update_diagnostic(DiagnosticType::DATA_STORAGE,
                                                          eros::Level::Type::ERROR,
                                                          Message::INITIALIZING_ERROR,
                                                          "Sonar Count is 0!");
        logger->log_diagnostic(diagnostic);

        return diagnostic_manager.get_diagnostics();
    }
    sonars = _sonars;
    for (auto type : diagnostic_types) {
        if (type != DiagnosticType::SOFTWARE) {
            diagnostic = diagnostic_manager.update_diagnostic(
                type, eros::Level::Type::INFO, Message::NOERROR, "Initialized.");
        }
    }
    return diagnostic_manager.get_diagnostics();
}
std::vector<eros::eros_diagnostic::Diagnostic> BaseSonarArrayNodeDriver::update(
    double current_time_sec, double dt) {
    if (prev_current_time_sec < 0) {
        prev_current_time_sec = current_time_sec;
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::SOFTWARE, eros::Level::Type::INFO, Message::NOERROR, "First Run.");
        return diagnostic_manager.get_diagnostics();
    }
    double elap_time = current_time_sec - prev_current_time_sec;

    run_time += elap_time;
    prev_current_time_sec = current_time_sec;
    // NO Practical way to Unit Test this
    // GCOVR_EXCL_START
    if (elap_time > (2.0 * dt)) {
        diagnostic =
            diagnostic_manager.update_diagnostic(DiagnosticType::SENSORS,
                                                 eros::Level::Type::WARN,
                                                 Message::DROPPING_PACKETS,
                                                 "Expected Update Time: " + std::to_string(dt) +
                                                     " Actual Time: " + std::to_string(elap_time));
        return diagnostic_manager.get_diagnostics();
    }
    // GCOVR_EXCL_STOP
    diagnostic = diagnostic_manager.update_diagnostic(
        DiagnosticType::SOFTWARE, eros::Level::Type::INFO, Message::NOERROR, "");

    return diagnostic_manager.get_diagnostics();
}

std::string BaseSonarArrayNodeDriver::pretty(std::string mode) {
    std::string str;
    if (mode == "") {
        str += BaseSonarArrayNodeDriver::pretty("simple");
        str += "\nRuntime: " + std::to_string(run_time) + " (sec).\n";
    }
    else if (mode == "simple") {
        str += "\tInitialized: " + std::to_string(fully_initialized) + "\n";
        str += eros::eros_diagnostic::DiagnosticUtility::pretty("\t", diagnostic, false);
    }
    return str;
}
std::string BaseSonarArrayNodeDriver::pretty(std::vector<sensor_msgs::Range> sonar_data) {
    std::string str = "";
    uint16_t index = 0;
    for (auto sonar : sonar_data) {
        str += "S: " + std::to_string(index) + ":R " + std::to_string(sonar.range) + " (m)";
        index++;
    }
    return str;
}
}  // namespace sonar_array