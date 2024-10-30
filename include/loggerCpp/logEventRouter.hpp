#pragma once

#include "utils.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

class LogSink;

/**
 * @brief Routes log events to appropriate sinks based on log level
 *
 * This class manages the routing of log events to registered logging sinks based on
 * their configured log levels. It provides thread-safe routing capabilities and
 * efficient cache-aligned data structures. Supports multiple sinks per log level.
 */
class LogEventRouter {
public:
    /**
     * @brief Default constructor
     */
    LogEventRouter() noexcept = default;

    /**
     * @brief Default destructor
     */
    ~LogEventRouter() = default;

    /**
     * @brief Deleted copy constructor to prevent shared state issues
     */
    LogEventRouter(const LogEventRouter&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent shared state issues
     */
    LogEventRouter& operator=(const LogEventRouter&) = delete;

    /**
     * @brief Move constructor for efficient resource transfer
     */
    LogEventRouter(LogEventRouter&&) noexcept = default;

    /**
     * @brief Move assignment operator for efficient resource transfer
     */
    LogEventRouter& operator=(LogEventRouter&&) noexcept = default;

    /**
     * @brief Adds a new route mapping between a log level and sink
     * @param level The log level to route
     * @param sink The sink to route messages to
     */
    void addRoute(utils::LogLevel level, std::shared_ptr<LogSink> sink) noexcept;

    /**
     * @brief Sets the current global log level
     * @param level The new log level to set
     */
    void setLogLevel(utils::LogLevel level) noexcept;

    /**
     * @brief Routes a log event to appropriate sinks based on level
     * @param event The log event to route
     */
    void routeEvent(const utils::LogEvent& event) noexcept;

private:
    alignas(64) std::unordered_map<utils::LogLevel, std::vector<std::shared_ptr<LogSink>>> routes; /**< Cache-aligned routing map supporting multiple sinks per level */
    alignas(64) utils::LogLevel currentLogLevel{utils::LogLevel::INFO}; /**< Cache-aligned current log level */
};