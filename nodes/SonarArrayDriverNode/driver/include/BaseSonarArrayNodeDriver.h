/**
 * @file BaseSonarArrayNodeDriver.h
 * @author David Gitz
 * @brief
 * @date 2025-02-23
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros_utility/ConvertUtility.h>
#include <eros_utility/PrettyUtility.h>

#include "ISonarArrayNodeDriver.h"
namespace sonar_array {

class BaseSonarArrayNodeDriver : public ISonarArrayNodeDriver
{
   public:
    BaseSonarArrayNodeDriver() {
    }
    virtual ~BaseSonarArrayNodeDriver() {
    }
    std::vector<eros::eros_diagnostic::Diagnostic> init(
        eros::eros_diagnostic::Diagnostic diagnostic,
        eros::Logger* logger,
        std::vector<sensor_msgs::Range> sonars);
    bool is_fully_initialized() {
        return fully_initialized;
    }

    std::vector<eros::eros_diagnostic::Diagnostic> update(double current_time_sec, double dt);

    std::string pretty(std::string mode);
    std::vector<sensor_msgs::Range> get_sonar_data() {
        return sonars;
    }
    double get_runtime() {
        return run_time;
    }
    std::string pretty(std::vector<sensor_msgs::Range> sonar_data);
    uint64_t get_good_packet_count() {
        return good_packet_count;
    }
    uint64_t get_missed_packet_count() {
        return missed_packet_count;
    }
    uint64_t get_bad_packet_count() {
        return bad_packet_count;
    }
    double get_good_packet_rate() {
        good_packet_rate = (double)get_good_packet_count() / get_runtime();
        return good_packet_rate;
    }
    double get_missed_packet_rate() {
        missed_packet_rate = (double)get_missed_packet_count() / get_runtime();
        return missed_packet_rate;
    }
    double get_bad_packet_rate() {
        bad_packet_rate = (double)get_bad_packet_count() / get_runtime();
        return bad_packet_rate;
    }

   protected:
    eros::eros_diagnostic::Diagnostic diagnostic;
    eros::eros_diagnostic::DiagnosticManager diagnostic_manager;
    eros::Logger* logger;
    bool fully_initialized{false};
    std::vector<sensor_msgs::Range> sonars;
    uint64_t good_packet_count{0};
    uint64_t missed_packet_count{0};
    uint64_t bad_packet_count{0};
    double good_packet_rate{0.0};
    double missed_packet_rate{0.0};
    double bad_packet_rate{0.0};

   private:
    double prev_current_time_sec{-1.0};
    double run_time{0.0};
};
}  // namespace sonar_array