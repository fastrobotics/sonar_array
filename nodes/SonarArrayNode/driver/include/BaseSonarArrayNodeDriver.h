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
    bool init(eros::Logger* logger);
    bool is_fully_initialized() {
        return fully_initialized;
    }

    bool update(double current_time_sec, double dt);

    std::string pretty(std::string mode);

   protected:
    eros::Logger* logger;
    bool fully_initialized{false};

   private:
    double prev_current_time_sec{-1.0};
    double run_time{0.0};
};
}  // namespace sonar_array