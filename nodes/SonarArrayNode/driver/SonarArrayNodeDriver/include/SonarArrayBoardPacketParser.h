/**
 * @file SonarArrayBoardPacketParser.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <stdlib.h>

#include <boost/algorithm/string.hpp>
#include <string>
#include <vector>

#include "ros/time.h"
namespace sonar_array {
class SonarArrayBoardPacketParser
{
   public:
    enum class PacketType { UNKNOWN = 0, DATA_STREAM = 1, END_OF_LIST = 2 };
    struct ParsedPacket {
        bool parsed_ok{false};
        ros::Time time_stamp;
        PacketType packet_type;
        uint16_t sequence_number{0};
        uint8_t sonar_count{0};
        std::vector<uint16_t> sonar_values_cm;
    };
    SonarArrayBoardPacketParser();
    virtual ~SonarArrayBoardPacketParser();
    static ParsedPacket parsePacket(std::string str);
};
}  // namespace sonar_array