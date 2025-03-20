#include <chrono>
#include <csignal>

#include "SonarArrayNodeDriver.h"
using namespace sonar_array;
ISonarArrayNodeDriver* driver = new SonarArrayNodeDriver();
void printHelp() {
    printf("Tester for Sonar Array Node Driver\n");
    printf("-h This Menu.\n");
    printf("-d Device.  Default: /dev/ttyUSB0\n");
    printf("-s Sonar Count. Default: 20\n");
    printf("-l Logger Threshold. [DEBUG,INFO,NOTICE,WARN,ERROR]\n");
}
void signalinterrupt_handler(int sig) {
    printf("Killing Sonar Array Node Driver with Signal: %d\n", sig);
    driver->finish();
    delete driver;
    exit(0);
}
int main(int argc, char* argv[]) {
    signal(SIGINT, signalinterrupt_handler);
    signal(SIGTERM, signalinterrupt_handler);
    ros::Time::init();
    std::string logger_threshold = "DEBUG";
    std::string device = "/dev/ttyUSB0";
    uint16_t sonar_count = 20;
    for (;;) {
        switch (getopt(argc,
                       argv,
                       "d:s:l:h"))  // note the colon (:) to indicate that 'b' has a parameter and
                                    // is not a switch
        {
            case 'd': device = optarg; continue;
            case 's': sonar_count = atoi(optarg); continue;
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

    logger->log_debug("Starting Sonar Array Node Driver with " + std::to_string(sonar_count) +
                      " Sonars.");
    std::vector<sensor_msgs::Range> sonars;
    sonars.resize(sonar_count);
    driver->init(diag, logger, sonars);
    if (driver->set_comm_device(device, B115200) == false) {
        logger->log_error("Error Initializing Driver.  Exiting.");
        return 1;
    }
    double delta_time_sec = 0.02;
    while (true) {
        auto current_time = std::chrono::system_clock::now();
        auto duration_in_seconds = std::chrono::duration<double>(current_time.time_since_epoch());

        double current_time_sec = duration_in_seconds.count();
        driver->update(current_time_sec, delta_time_sec);
        usleep(delta_time_sec * 1000000);

        logger->log_debug(driver->pretty());
        logger->log_info(driver->pretty(driver->get_sonar_data()));
    }

    logger->log_debug("Sonar Array Node Driver Finished.");
    delete logger;
    return 0;
}