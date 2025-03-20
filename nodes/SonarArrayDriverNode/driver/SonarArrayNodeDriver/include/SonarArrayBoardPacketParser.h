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
    enum class PacketType {
        UNKNOWN = 0,     /*!< Uninitialized value. */
        DATA_STREAM = 1, /*!< Data Stream Packet filled with Sonar Data. */
        END_OF_LIST = 2  /*!< Last item of list. Used for Range Checks. */
    };
    struct ParsedPacket {
        bool parsed_ok{false};
        ros::Time time_stamp;
        PacketType packet_type;
        uint16_t sequence_number{0};
        uint8_t sonar_count{0};
        std::vector<double> sonar_values_m;
    };
    SonarArrayBoardPacketParser() = default;
    virtual ~SonarArrayBoardPacketParser() = default;
    static ParsedPacket parsePacket(std::string str);
};
}  // namespace sonar_array