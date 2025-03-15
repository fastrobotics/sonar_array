/**
 * @file SonarArrayNodeDriver.h
 * @author David Gitz
 * @brief
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros/Logger.h>
#include <eros_utility/ConvertUtility.h>
#include <eros_utility/PrettyUtility.h>
#include <errno.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#include "BaseSonarArrayNodeDriver.h"
#include "SonarArrayBoardPacketParser.h"

//! sonar_array Namespace
namespace sonar_array {
/**
 * @brief SonarArrayNodeDriver Class
 * @details
 */
class SonarArrayNodeDriver : public BaseSonarArrayNodeDriver
{
   public:
    SonarArrayNodeDriver();
    virtual ~SonarArrayNodeDriver();
    /**
     * @brief Initialize Sonar Array Node Driver
     *
     * @param logger
     * @return true
     * @return false
     */
    bool init(eros::eros_diagnostic::Diagnostic diagnostic,
              eros::Logger* logger,
              std::vector<sensor_msgs::Range> sonars) override;
    eros::eros_diagnostic::Diagnostic update(double current_time_sec, double dt) override;

    bool set_comm_device(std::string comm_device, int speed);
    /**
     * @brief Finish and Close Driver
     *
     * @return true
     * @return false
     */
    bool finish() override;
    std::string pretty(std::string mode = "") override;
    int readFromSerialPort(char* buffer, size_t size);
    bool processSequenceNumber(uint16_t sequence_number);
    bool updateSonarData(SonarArrayBoardPacketParser::ParsedPacket packet);

   private:
    bool first_run{true};
    std::string comm_device_;
    int fd;
    uint64_t good_packet_count{0};
    uint64_t bad_packet_count{0};
    uint16_t latest_sequence_number{0};
};
}  // namespace sonar_array