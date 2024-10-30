#pragma once

#include "utils.hpp"

#include <source_location>
#include <fstream>
#include <string_view>

/**
 * @brief Abstract base class for log sinks
 *
 * This class defines the interface for all logging sinks. A sink represents a destination
 * where log messages can be written, such as console, file, network, or database.
 */
class LogSink {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~LogSink() noexcept = default;

    /**
     * @brief Pure virtual function to write a log event
     * @param event The log event to be written
     */
    virtual void write(const utils::LogEvent& event) = 0;

protected:
    /**
     * @brief Protected default constructor
     */
    LogSink() noexcept = default;

    /**
     * @brief Deleted copy constructor to prevent copying
     */
    LogSink(const LogSink&) = delete;

    /**
     * @brief Deleted copy assignment operator to prevent copying
     */
    LogSink& operator=(const LogSink&) = delete;

    /**
     * @brief Move constructor
     */
    LogSink(LogSink&&) noexcept = default;

    /**
     * @brief Move assignment operator
     */
    LogSink& operator=(LogSink&&) noexcept = default;
};
