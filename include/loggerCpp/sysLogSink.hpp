#pragma once

#include "loggerCpp/logSink.hpp"

#include <string_view>
#include <syslog.h>

/**
 * @brief System log (syslog) sink for logging
 * 
 * This class implements a logging sink that writes log messages to the system logger (syslog).
 * It inherits from the LogSink base class and provides syslog-specific logging functionality.
 */
class SysLogSink final : public LogSink {
public:
    /**
     * @brief Constructs a SysLogSink with the specified identity and facility
     * 
     * @param ident The string identifier to prepend to syslog messages
     * @param facility The syslog facility to use (e.g. LOG_USER, LOG_LOCAL0)
     */
    explicit SysLogSink(std::string_view ident, int facility = LOG_USER);

    /**
     * @brief Destructor that closes the syslog connection
     */
    ~SysLogSink() noexcept override;

    /**
     * @brief Writes a log event to syslog
     * 
     * @param event The log event containing the message and metadata to be written
     * @throws None This function is noexcept
     * 
     * This function formats and writes the provided log event to the system logger
     * using the configured facility and appropriate priority level.
     */
    void write(const utils::LogEvent& event) override;

private:
    /**
     * @brief Converts LogLevel to syslog priority
     * 
     * @param level The LogLevel to convert
     * @return The corresponding syslog priority
     */
    static int logLevelToSyslogPriority(utils::LogLevel level) noexcept;
};
