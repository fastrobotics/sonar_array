#include "SonarArrayNodeDriver.h"
namespace sonar_array {
SonarArrayNodeDriver::SonarArrayNodeDriver() {
}
SonarArrayNodeDriver::~SonarArrayNodeDriver() {
    printf("Closing\n");
    close(fd);
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
    bool status = BaseSonarArrayNodeDriver::update(dt);
    if (status == false) {
        return status;
    }

    char buffer[100];
    /*
    int n = readFromSerialPort(buffer, sizeof(buffer));
    if (n < 0) {
        status = false;
        logger->log_error(strerror(errno));
    }
    else {
        logger->log_debug("Read: " + std::string(buffer, n));
        status = true;
    }
        */
    return status;
}
std::string SonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Sonar Array Node Driver";
    str += " Comm Device: " + comm_device_ + "\n";
    str += BaseSonarArrayNodeDriver::pretty(mode);
    return str;
}
bool SonarArrayNodeDriver::set_comm_device(std::string comm_device, int speed) {
    comm_device_ = comm_device;
    fd = open(comm_device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        logger->log_error("Error Opening: " + comm_device + " Exception: " + strerror(errno));
        return false;
    }
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        logger->log_error(strerror(errno));
        return false;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit characters
    tty.c_iflag &= ~IGNBRK;                      // disable break processing
    tty.c_lflag = 0;                             // no signaling chars, no echo, no
                                                 // canonical processing
    tty.c_oflag = 0;                             // no remapping, no delays
    tty.c_cc[VMIN] = 0;                          // read doesn't block
    tty.c_cc[VTIME] = 5;                         // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);    // ignore modem controls,
                                        // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);  // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        logger->log_error(strerror(errno));
        return false;
    }
    fully_initialized = true;
    return true;
}
int SonarArrayNodeDriver::readFromSerialPort(char* buffer, size_t size) {
    return read(fd, buffer, size);
}
}  // namespace sonar_array