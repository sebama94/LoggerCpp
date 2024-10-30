#include "loggerCpp/sysLogSink.hpp"
#include <format>

SysLogSink::SysLogSink(std::string_view ident, int facility) {
    // Open syslog connection with specified identity and facility
    openlog(ident.data(), LOG_PID | LOG_NDELAY, facility);
}

SysLogSink::~SysLogSink() noexcept {
    // Close syslog connection
    closelog();
}

void SysLogSink::write(const utils::LogEvent& event) {
    // Format message with timestamp and location info
    std::string formatted_message = std::format("{} (function: {} line: {})",
        event.message, 
        event.location.function_name(),
        event.location.line()
    );

    // Write to syslog with appropriate priority level
    syslog(logLevelToSyslogPriority(event.level), "%s", formatted_message.c_str());
}

int SysLogSink::logLevelToSyslogPriority(utils::LogLevel level) noexcept {
    switch (level) {
        case utils::LogLevel::DEBUG:
            return LOG_DEBUG; 
        case utils::LogLevel::INFO:
            return LOG_INFO;
        case utils::LogLevel::WARNING:
            return LOG_WARNING;
        case utils::LogLevel::ERROR:
            return LOG_ERR;
        case utils::LogLevel::CRITICAL:
            return LOG_CRIT;
        default:
            return LOG_NOTICE;
    }
}
