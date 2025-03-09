#include <chrono>

#include "SonarArrayNodeDriver.h"
using namespace sonar_array;
SonarArrayNodeDriver driver;
int main() {
    eros::Logger* logger = new eros::Logger("DEBUG", "exec_SonarArrayNodeDriver");
    logger->log_debug("Starting Sonar Array Node Driver");

    driver.init(logger);
    if (driver.set_comm_device("/dev/ttyUSB0", B115200) == false) {
        logger->log_error("Error Initializing Driver.  Exiting.");
        return 1;
    }
    double delta_time_sec = 1.0;
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