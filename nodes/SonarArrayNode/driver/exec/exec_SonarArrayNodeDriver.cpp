#include "SonarArrayNodeDriver.h"
using namespace sonar_array;
SonarArrayNodeDriver driver;
int main() {
    eros::Logger* logger = new eros::Logger("DEBUG", "exec_SonarArrayNodeDriver");
    logger->log_debug("Starting Sonar Array Node Driver");

    driver.init(logger);
    if (driver.set_comm_device("test_device") == false) {
        logger->log_error("Error Initializing Driver.  Exiting.");
        return 1;
    }
    double delta_time_sec = 0.25;
    while (true) {
        driver.update(delta_time_sec);
        usleep(delta_time_sec * 1000000);
        logger->log_debug(driver.pretty());
    }

    logger->log_debug("Sonar Array Node Driver Finished.");
    delete logger;
    return 0;
}