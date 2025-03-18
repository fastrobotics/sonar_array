#include "SonarArrayBoardPacketParser.h"

namespace sonar_array {
SonarArrayBoardPacketParser::SonarArrayBoardPacketParser() {
}
SonarArrayBoardPacketParser::~SonarArrayBoardPacketParser() {
}
SonarArrayBoardPacketParser::ParsedPacket SonarArrayBoardPacketParser::parsePacket(
    std::string str) {
    ParsedPacket data;
    try {
        // If it's an empty string, don't try anything.
        if (str.size() == 0) {
            return data;
        }
        if (str.size() < 9) {  // Can't do anything with a packet smaller than this
            return data;
        }
        // If the packet doesn't start with the correct start character
        if (str.at(0) != '$') {
            std::size_t res = str.find('$');
            if (res != std::string::npos) {
                str = str.substr(res);
            }
            else {
                return data;
            }
        }
        if (str.substr(1, 2) == "AA") {
            // Drop first 3 characters from string
            std::string data_str = str.substr(3, str.size());
            data.packet_type = SonarArrayBoardPacketParser::PacketType::DATA_STREAM;
            std::string v1 = data_str.substr(0, 4);
            data.sequence_number = atoi(v1.c_str());
            std::string v2 = data_str.substr(4, 2);
            data.sonar_count = atoi(v2.c_str());
            if (data.sonar_count == 0) {  // No Sonar Data, invalid Packet
                return data;
            }
            uint16_t min_data_size = 4 + 2 + data.sonar_count * 4;
            if (data_str.size() < min_data_size) {  // Incomplete Packet, throw away
                return data;
            }
            data.sonar_values_cm.resize(data.sonar_count);
            uint16_t offset = 6;
            for (uint8_t i = 0; i < data.sonar_count; ++i) {
                std::string v = data_str.substr(offset, 4);
                data.sonar_values_cm[i] = atoi(v.c_str());
                offset += 4;
            }
            data.parsed_ok = true;
        }
    }
    catch (const std::exception& ex) {
        return data;
    }
    catch (const std::string& ex) {
        return data;
    }
    catch (...) {
        return data;
    }
    return data;
}
}  // namespace sonar_array
