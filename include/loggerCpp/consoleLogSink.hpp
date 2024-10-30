#pragma once

#include "logSink.hpp"

#include <string_view>
#include <fstream>

/**
 * @brief Console output sink for logging
 * 
 * This class implements a logging sink that writes log messages to the console (stdout/stderr).
 * It inherits from the LogSink base class and provides console-specific logging functionality.
 */
class ConsoleLogSink final : public LogSink {
public:
    /**
     * @brief Default constructor
     * 
     * Constructs a ConsoleLogSink object that can write log messages to the console.
     */
    ConsoleLogSink() noexcept = default;

    /**
     * @brief Writes a log event to the console
     * 
     * @param event The log event containing the message and metadata to be written
     * @throws None This function is noexcept
     * 
     * This function formats and writes the provided log event to the appropriate 
     * console stream (stdout for regular logs, stderr for errors).
     */
    void write(const utils::LogEvent& event) override;
};
