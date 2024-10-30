#pragma once
#include <string>
#include <string_view>

#include "loggingEngine.hpp"
#include <fmt/core.h>

/**
 * @brief Configuration manager class for setting up logging sinks and levels
 * 
 * This class manages the configuration of the logging system, including setting up
 * different types of logging sinks (console, file, network, database) and their 
 * associated log levels.
 */
class ConfigurationManager {
public:
    /**
     * @brief Default constructor
     */
    ConfigurationManager() = default;

    /**
     * @brief Virtual destructor
     */
    ~ConfigurationManager() noexcept = default;

    /**
     * @brief Deleted copy constructor to prevent copying
     */
    ConfigurationManager(const ConfigurationManager&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying
     */
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;
    
    /**
     * @brief Move constructor
     * @note Allows efficient transfer of resources
     */
    ConfigurationManager(ConfigurationManager&&) noexcept = default;

    /**
     * @brief Move assignment operator
     * @return Reference to the moved ConfigurationManager
     */
    ConfigurationManager& operator=(ConfigurationManager&&) noexcept = default;

    /**
     * @brief Constructs a ConfigurationManager with specified log level
     * @param logLevel The global log level to set for the logger
     */
    explicit ConfigurationManager(utils::LogLevel logLevel);

    /**
     * @brief Configures and adds a console sink to the logger
     * @param level The minimum log level for messages to be written to console
     */
    void applyConsoleSink(const utils::LogLevel& level);

    /**
     * @brief Configures and adds a file sink to the logger
     * @param level The minimum log level for messages to be written to file
     * @param filename The path and name of the log file
     */
    void applyFileSink(const utils::LogLevel& level, const std::string_view& filename);

    /**
     * @brief Configures and adds a network sink to the logger
     * @param level The minimum log level for messages to be sent over network
     * @param url The destination URL for network logging
     */
    void applyNetworkSink(const utils::LogLevel& level, const std::string_view& url);

    /**
     * @brief Configures and adds a database sink to the logger
     * @param level The minimum log level for messages to be stored in database
     * @param database The database connection string or identifier
     */
    void applyDataBaseSink(const utils::LogLevel& level, const std::string_view& database);

};