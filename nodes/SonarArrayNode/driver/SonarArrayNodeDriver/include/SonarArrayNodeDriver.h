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
    bool init(eros::Logger* logger) override;
    /**
     * @brief Finish and Close Driver
     *
     * @return true
     * @return false
     */
    bool set_comm_device(std::string comm_device);
    bool finish() override;
    std::string pretty(std::string mode = "") override;

   private:
    std::string comm_device_;
    int fd;
};
}  // namespace sonar_array