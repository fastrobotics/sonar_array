#include <chrono>

#include "SonarArrayNodeDriver.h"
using namespace sonar_array;
SonarArrayNodeDriver driver;
void printHelp() {
    printf("Tester for Sonar Array Node Driver\n");
    printf("-h This Menu.\n");
    printf("-l Logger Threshold. [DEBUG,INFO,NOTICE,WARN,ERROR]\n");
}
int main(int argc, char* argv[]) {
    std::string logger_threshold = "DEBUG";
    for (;;) {
        switch (getopt(argc,
                       argv,
                       "l:h"))  // note the colon (:) to indicate that 'b' has a parameter and
                                // is not a switch
        {
            case 'l': logger_threshold = optarg; break;
            case '?': printHelp(); return 0;
            case 'h': printHelp(); return 0;
            default: printHelp(); return 0;
        }

        break;
    }
    eros::Logger* logger = new eros::Logger(logger_threshold, "exec_SonarArrayNodeDriver");
    eros::eros_diagnostic::Diagnostic diag =
        eros::eros_diagnostic::Diagnostic("UnitTest",
                                          "UnitTest",
                                          eros::System::MainSystem::SIMROVER,
                                          eros::System::SubSystem::ENTIRE_SYSTEM,
                                          eros::System::Component::MAPPING,
                                          eros::eros_diagnostic::DiagnosticType::SENSORS,
                                          eros::eros_diagnostic::Message::INITIALIZING,
                                          eros::Level::Type::INFO,
                                          "Initializing");

    logger->log_debug("Starting Sonar Array Node Driver");

    driver.init(diag, logger);
    if (driver.set_comm_device("/dev/ttyUSB0", B115200) == false) {
        logger->log_error("Error Initializing Driver.  Exiting.");
        return 1;
    }
    double delta_time_sec = 0.1;
    while (true) {
        auto current_time = std::chrono::system_clock::now();
        auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());

        double current_time_sec = duration_in_seconds.count();
        driver.update(current_time_sec, delta_time_sec);
        usleep(delta_time_sec * 1000000);

        logger->log_debug(driver.pretty());
    }

    logger->log_debug("Sonar Array Node Driver Finished.");
    delete logger;
    return 0;
}