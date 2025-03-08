/**
 * @file SonarArrayNodeDriver.h
 * @author David Gitz
 * @brief
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once
#include <eros/Logger.h>
#include <eros_utility/ConvertUtility.h>
#include <eros_utility/PrettyUtility.h>

//! sonar_array Namespace
namespace sonar_array {
/**
 * @brief SonarArrayNodeDriver Class
 * @details
 */
class SonarArrayNodeDriver
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
    bool init(eros::Logger* logger);
    /**
     * @brief Update SonarArrayNodeDriver
     * @details
     *
     * @param dt Delta Time in seconds.
     * @return true
     * @return false
     */
    bool update(double dt);
    /**
     * @brief Finish and Close Driver
     *
     * @return true
     * @return false
     */
    bool finish();
    std::string pretty();

   private:
    eros::Logger* logger;
};
}  // namespace sonar_array