#include "SonarArrayNodeDriver.h"
// No practical way to unit test this
// GCOVR_EXCL_START
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
bool SonarArrayNodeDriver::init(eros::eros_diagnostic::Diagnostic _diagnostic,
                                eros::Logger* _logger) {
    return BaseSonarArrayNodeDriver::init(_diagnostic, _logger);
}
eros::eros_diagnostic::Diagnostic SonarArrayNodeDriver::update(double current_time_sec, double dt) {
    auto diag = BaseSonarArrayNodeDriver::update(current_time_sec, dt);
    if (diag.level >= eros::Level::Type::ERROR) {
        logger->log_diagnostic(diag);
        return diag;
    }

    char buffer[100];

    int n = readFromSerialPort(buffer, sizeof(buffer));
    if (n < 0) {
        diag.type = eros::eros_diagnostic::DiagnosticType::COMMUNICATIONS;
        diag.level = eros::Level::Type::ERROR;
        diag.message = eros::eros_diagnostic::Message::DROPPING_PACKETS;
        diag.description = strerror(errno);
        logger->log_diagnostic(diag);
        diagnostic = diag;
        return diag;
    }
    else {
        if (diag.level >= eros::Level::Type::WARN) {
            diagnostic = diag;
            logger->log_diagnostic(diag);
            return diag;
        }
        diag.type = eros::eros_diagnostic::DiagnosticType::SOFTWARE;
        diag.level = eros::Level::Type::INFO;
        diag.message = eros::eros_diagnostic::Message::NOERROR;
        diag.description = "";
        diagnostic = diag;
        return diag;
    }
}
std::string SonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Sonar Array Node Driver";
    str += " Comm Device: " + comm_device_ + "\n";
    str += BaseSonarArrayNodeDriver::pretty(mode);
    return str;
}
bool SonarArrayNodeDriver::set_comm_device(std::string comm_device, int speed) {
    comm_device_ = comm_device;
    fd = open(comm_device.c_str(), O_RDWR);  // | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        logger->log_error("Error Opening: " + comm_device + " Exception: " + strerror(errno));
        return false;
    }
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        logger->log_error(strerror(errno));
        return false;
    }
    tty.c_cflag &= ~PARENB;  // Clear parity bit, disabling parity (most common)
    tty.c_cflag &=
        ~CSTOPB;  // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE;          // Clear all bits that set the data size
    tty.c_cflag |= CS8;             // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS;        // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL;  // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;                    // Disable echo
    tty.c_lflag &= ~ECHOE;                   // Disable erasure
    tty.c_lflag &= ~ECHONL;                  // Disable new-line echo
    tty.c_lflag &= ~ISIG;                    // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR |
                     ICRNL);  // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST;  // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR;  // Prevent conversion of newline to carriage return/line feed
    // tty.c_oflag &= ~OXTABS; // Prevent conversion of tabs to spaces (NOT PRESENT ON LINUX)
    // tty.c_oflag &= ~ONOEOT; // Prevent removal of C-d chars (0x004) in output (NOT PRESENT ON
    // LINUX)

    tty.c_cc[VTIME] =
        10;  // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);
    /*
        cfsetospeed(&tty, speed);
        cfsetispeed(&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;  // 8-bit characters
        tty.c_iflag &= ~IGNBRK;                      // disable break processing
        tty.c_lflag = 0;                             // no signaling chars, no echo, no
                                                     // canonical processing
        tty.c_oflag = 0;                             // no remapping, no delays
        tty.c_cc[VMIN] = 0;                          // read doesn't block
        tty.c_cc[VTIME] = 0.1;                       // 0.1 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY);  // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);    // ignore modem controls,
                                            // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);  // shut off parity
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;
    */
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        logger->log_error(strerror(errno));
        return false;
    }
    fully_initialized = true;
    logger->log_notice("Sonar Array Node Driver Fully Initialized.");
    return true;
}
int SonarArrayNodeDriver::readFromSerialPort(char* buffer, size_t size) {
    return read(fd, buffer, size);
}
// GCOVR_EXCL_STOP
}  // namespace sonar_array
