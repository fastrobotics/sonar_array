#include "SonarArrayNodeDriver.h"
// No practical way to unit test this
// GCOVR_EXCL_START
using namespace eros::eros_diagnostic;
namespace sonar_array {
SonarArrayNodeDriver::SonarArrayNodeDriver() {
}
SonarArrayNodeDriver::~SonarArrayNodeDriver() {
    close(fd);
    finish();
}
bool SonarArrayNodeDriver::finish() {
    return true;
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayNodeDriver::init(
    eros::eros_diagnostic::Diagnostic _diagnostic,
    eros::Logger* _logger,
    std::vector<sensor_msgs::Range> _sonars) {
    return BaseSonarArrayNodeDriver::init(_diagnostic, _logger, _sonars);
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayNodeDriver::update(double current_time_sec,
                                                                            double dt) {
    BaseSonarArrayNodeDriver::update(current_time_sec, dt);
    if (diagnostic_manager.get_highest_level() >= eros::Level::Type::ERROR) {
        return diagnostic_manager.get_diagnostics();
    }

    char buffer[200];
    int num_bytes_read = readFromSerialPort(buffer, sizeof(buffer));

    if (num_bytes_read < 0) {
        diagnostic = diagnostic_manager.update_diagnostic(DiagnosticType::SENSORS,
                                                          eros::Level::Type::ERROR,
                                                          Message::DROPPING_PACKETS,
                                                          strerror(errno));
        logger->log_diagnostic(diagnostic);
        return diagnostic_manager.get_diagnostics();
    }
    else {
        SonarArrayBoardPacketParser::ParsedPacket packet =
            SonarArrayBoardPacketParser::parsePacket(buffer);
        if (packet.parsed_ok == true) {
            if (processSequenceNumber(packet.sequence_number)) {
                if (packet.sonar_count != sonars.size()) {
                    diagnostic = diagnostic_manager.update_diagnostic(
                        DiagnosticType::SENSORS,
                        eros::Level::Type::WARN,
                        Message::DROPPING_PACKETS,
                        "Unexpected Number of Sonars!  " + std::to_string(packet.sonar_count) +
                            " != " + std::to_string(sonars.size()));
                    logger->log_diagnostic(diagnostic);
                    return diagnostic_manager.get_diagnostics();
                }
                else {
                    good_packet_count++;
                    packet.time_stamp = ros::Time::now();
                    updateSonarData(packet);
                }
            }
            else {
                missed_packet_count++;
            }
        }
        else {
            bad_packet_count++;
        }
    }

    if (good_packet_rate > 8.0) {
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::SOFTWARE, eros::Level::Type::INFO, Message::NOERROR, "Driver Ok");
        logger->log_diagnostic(diagnostic);
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::SENSORS,
            eros::Level::Type::INFO,
            Message::NOERROR,
            "Good Packet Rate: " + std::to_string(get_good_packet_rate()) + " (Hz)");
    }
    else if (missed_packet_rate > 1.0) {
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::SENSORS,
            eros::Level::Type::WARN,
            Message::DROPPING_PACKETS,
            "Missed Packet Rate: " + std::to_string(get_missed_packet_rate()) + " (Hz)");
    }
    else if (bad_packet_rate > 1.0) {
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::SENSORS,
            eros::Level::Type::WARN,
            Message::DROPPING_PACKETS,
            "Bad Packet Rate: " + std::to_string(get_bad_packet_rate()) + " (Hz)");
    }
    return diagnostic_manager.get_diagnostics();
}
std::string SonarArrayNodeDriver::pretty(std::string mode) {
    std::string str = "Sonar Array Node Driver";
    str += " Comm Device: " + comm_device_ + "\n";
    str += BaseSonarArrayNodeDriver::pretty(mode) + "\n";
    str += "Good Packets: " + std::to_string(good_packet_count) +
           " Rate: " + std::to_string(get_good_packet_rate()) +
           " (Hz) Missed Packets: " + std::to_string(missed_packet_count) +
           " Rate: " + std::to_string(get_missed_packet_rate()) +
           " (Hz) Bad Packets: " + std::to_string(bad_packet_count) +
           " Rate: " + std::to_string(get_bad_packet_rate()) + " (Hz)\n";
    return str;
}
std::vector<eros::eros_diagnostic::Diagnostic> SonarArrayNodeDriver::set_comm_device(
    std::string comm_device, int speed) {
    diagnostic = diagnostic_manager.update_diagnostic(DiagnosticType::COMMUNICATIONS,
                                                      eros::Level::Type::INFO,
                                                      Message::INITIALIZING,
                                                      "Initializing");
    comm_device_ = comm_device;
    fd = open(comm_device.c_str(), O_RDWR);  // | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::COMMUNICATIONS,
            eros::Level::Type::ERROR,
            Message::INITIALIZING_ERROR,
            "Error Opening: " + comm_device + " Exception: " + strerror(errno));
        logger->log_diagnostic(diagnostic);
        return diagnostic_manager.get_diagnostics();
    }
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::COMMUNICATIONS,
            eros::Level::Type::ERROR,
            Message::INITIALIZING_ERROR,
            std::string("Error Reading Comm Port Attributes. Exception: ") +
                std::string(strerror(errno)));
        logger->log_diagnostic(diagnostic);
        return diagnostic_manager.get_diagnostics();
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

    tty.c_cc[VTIME] =
        10;  // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 115200
    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);
    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        diagnostic = diagnostic_manager.update_diagnostic(
            DiagnosticType::COMMUNICATIONS,
            eros::Level::Type::ERROR,
            Message::INITIALIZING_ERROR,
            std::string("Error Setting Comm Port Attributes. Exception: ") +
                std::string(strerror(errno)));
        logger->log_diagnostic(diagnostic);
        return diagnostic_manager.get_diagnostics();
    }
    fully_initialized = true;

    diagnostic = diagnostic_manager.update_diagnostic(
        DiagnosticType::COMMUNICATIONS,
        eros::Level::Type::INFO,
        Message::NOERROR,
        "Sonar Array Node Driver Comm Port Fully Initialized.");
    return diagnostic_manager.get_diagnostics();
}
int SonarArrayNodeDriver::readFromSerialPort(char* buffer, size_t size) {
    return read(fd, buffer, size);
}
bool SonarArrayNodeDriver::processSequenceNumber(uint16_t sequence_number) {
    bool status = false;
    if (first_run) {
        latest_sequence_number = sequence_number;
        first_run = false;
        status = true;
    }
    else {
        if ((sequence_number == 0) && (latest_sequence_number == 9999)) {
            status = true;
        }
        else {
            uint16_t delta = sequence_number - latest_sequence_number;
            if (delta <= 1) {
                status = true;
            }
            else {
                status = false;
            }
        }
    }
    latest_sequence_number = sequence_number;
    return status;
}
bool SonarArrayNodeDriver::updateSonarData(SonarArrayBoardPacketParser::ParsedPacket packet) {
    if (packet.sonar_values_m.size() != sonars.size()) {
        return false;
    }

    for (std::size_t i = 0; i < packet.sonar_values_m.size(); ++i) {
        sonars[i].header.stamp = packet.time_stamp;
        sonars[i].range = packet.sonar_values_m[i];
    }
    return true;
}
}  // namespace sonar_array

// GCOVR_EXCL_STOP