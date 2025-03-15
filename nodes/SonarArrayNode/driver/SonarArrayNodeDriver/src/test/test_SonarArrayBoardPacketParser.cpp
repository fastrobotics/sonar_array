/**
 * @file test_SonarArrayBoardPacketParser.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-14
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <gtest/gtest.h>
#include <stdio.h>

#include "../../include/SonarArrayBoardPacketParser.h"
using namespace sonar_array;
//
TEST(BasicTest, ParseMessage_DataStream) {
    {  // Normal Packet
        // clang-format off
        std::string packet =
            "$AA65122000910091009100910091009100910091009100910091009100910091009100910091009100910091";
        // clang-format on
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_EQ(data.packet_type, SonarArrayBoardPacketParser::PacketType::DATA_STREAM);
        EXPECT_EQ(data.sequence_number, 6512);
        EXPECT_EQ(data.sonar_count, 20);
        EXPECT_EQ(data.sonar_values_cm.size(), data.sonar_count);
        for (auto v : data.sonar_values_cm) { EXPECT_EQ(v, 91); }
        EXPECT_TRUE(data.parsed_ok);
    }
    {  // Packet with missing data at start, but then complete.
        // clang-format off
        std::string packet =
            "09100910091$AA65122000910091009100910091009100910091009100910091009100910091009100910091009100910091";
        // clang-format on
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_TRUE(data.parsed_ok);
    }
}
TEST(BasicTest, ParseMessage_MalformedPackets) {
    {  // Empty String
        std::string packet = "";
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_FALSE(data.parsed_ok);
    }
    {  // No start character
       // clang-format off
         std::string packet =
         "AA65122000910091009100910091009100910091009100910091009100910091009100910091009100910091";
        // clang-format on
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_FALSE(data.parsed_ok);
    }
    {  // Incorrect Packet Type
        // clang-format off
        std::string packet =
        "$AB";
        // clang-format on
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_FALSE(data.parsed_ok);
    }
    {  // Incomplete Packet
        // clang-format off
        std::string packet =
            "$AA6512200091009100910091009100910091009100910091009100910091009100910091009100910091009"; // missing one character
        // clang-format on
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_FALSE(data.parsed_ok);
    }
    {  // Message with 0 Sonar Values
        // clang-format off
        std::string packet =
            "$AA651200";
        // clang-format on
        auto data = SonarArrayBoardPacketParser::parsePacket(packet);
        EXPECT_FALSE(data.parsed_ok);
    }
}
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
