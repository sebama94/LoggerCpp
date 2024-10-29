#include "loggerCpp/consoleLogSink.hpp"

#include <iostream>
#include <format>

void ConsoleLogSink::write(const utils::LogEvent& event) {
    // Format and output log level, timestamp, message and location
    std::cout << std::format("{} [{}] {}\n{} [{}] {} {} - ({}:{}:{})\n",
        utils::getColorForLogLevel(event.level),
        utils::getLogLevelString(event.level),
        COLOR_RESET,
        utils::getColorForLogLevel(event.level), 
        event.timestamp,
        COLOR_RESET,
        event.message,
        event.location.file_name(),
        event.location.line(),
        event.location.function_name());
}