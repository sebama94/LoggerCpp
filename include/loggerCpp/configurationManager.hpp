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
    ConfigurationManager();

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
    explicit ConfigurationManager(const utils::LogLevel& logLevel);

    /**
     * @brief Configures and adds multiple console sinks to the logger
     * @param level1 First log level
     * @param level2 Second log level
     * @param level3 Third log level (optional)
     * @param level4 Fourth log level (optional)
     * @throws std::runtime_error if sink creation fails
     */
    void applyConsoleSink(const utils::LogLevel& level);
    [[maybe_unused]] void applyConsoleSink(const utils::LogLevel& level1, const utils::LogLevel& level2);
    [[maybe_unused]] void applyConsoleSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3);
    [[maybe_unused]] void applyConsoleSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4);
    [[maybe_unused]] void applyConsoleSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const utils::LogLevel& level5);

    /**
     * @brief Configures and adds multiple file sinks to the logger
     * @param filename The path and name of the log file
     * @param level1 First log level
     * @param level2 Second log level
     * @param level3 Third log level (optional)
     * @param level4 Fourth log level (optional)
     * @throws std::runtime_error if file cannot be opened or sink creation fails
     */
    void applyFileSink(const utils::LogLevel& level, const std::string_view& filename);
    [[maybe_unused]] void applyFileSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const std::string_view& filename);
    [[maybe_unused]] void applyFileSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const std::string_view& filename);
    [[maybe_unused]] void applyFileSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const std::string_view& filename);
    [[maybe_unused]] void applyFileSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const utils::LogLevel& level5, const std::string_view& filename);

    /**
     * @brief Configures and adds multiple network sinks to the logger
     * @param url The destination URL for network logging
     * @param level1 First log level
     * @param level2 Second log level
     * @param level3 Third log level (optional)
     * @param level4 Fourth log level (optional)
     * @throws std::runtime_error if network connection fails or sink creation fails
     */
    void applyNetworkSink(const utils::LogLevel& level, const std::string_view& url);
    [[maybe_unused]] void applyNetworkSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const std::string_view& url);
    [[maybe_unused]] void applyNetworkSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const std::string_view& url);
    [[maybe_unused]] void applyNetworkSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const std::string_view& url);
    [[maybe_unused]] void applyNetworkSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const utils::LogLevel& level5, const std::string_view& url);

    /**
     * @brief Configures and adds multiple database sinks to the logger
     * @param database The database connection string
     * @param level1 First log level
     * @param level2 Second log level
     * @param level3 Third log level (optional)
     * @param level4 Fourth log level (optional)
     * @throws std::runtime_error if database connection fails or sink creation fails
     */
    void applyDataBaseSink(const utils::LogLevel& level, const std::string_view& database);
    [[maybe_unused]] void applyDataBaseSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const std::string_view& database);
    [[maybe_unused]] void applyDataBaseSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const std::string_view& database);
    [[maybe_unused]] void applyDataBaseSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const std::string_view& database);
    [[maybe_unused]] void applyDataBaseSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const utils::LogLevel& level5, const std::string_view& database);

    /**
     * @brief Configures and adds multiple syslog sinks to the logger
     * @param ident The string identifier to prepend to syslog messages
     * @param level1 First log level
     * @param level2 Second log level
     * @param level3 Third log level (optional)
     * @param level4 Fourth log level (optional)
     */
    #ifdef __unix__
    void applySysLogSink(const utils::LogLevel& level, const std::string_view& ident);  
    [[maybe_unused]] void applySysLogSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const std::string_view& ident);
    [[maybe_unused]] void applySysLogSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const std::string_view& ident);
    [[maybe_unused]] void applySysLogSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const std::string_view& ident);
    [[maybe_unused]] void applySysLogSink(const utils::LogLevel& level1, const utils::LogLevel& level2, const utils::LogLevel& level3, const utils::LogLevel& level4, const utils::LogLevel& level5, const std::string_view& ident);
    #endif
};