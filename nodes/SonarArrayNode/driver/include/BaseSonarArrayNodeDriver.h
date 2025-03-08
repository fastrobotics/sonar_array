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
    bool is_fully_initialized() {
        return fully_initialized;
    }

    bool update(double dt) {
        run_time += dt;
        return true;
    }

    std::string pretty(std::string mode) {
        std::string str;
        if (mode == "") {
            str += pretty("simple");
            str += "\nRuntime: " + std::to_string(run_time) + " (sec).\n";
        }
        else if (mode == "simple") {
            str += "\tInitialized: " + std::to_string(fully_initialized) + "\n";
        }
        return str;
    }

   protected:
    eros::Logger* logger;
    bool fully_initialized{false};

   private:
    double run_time{0.0};
};
}  // namespace sonar_array