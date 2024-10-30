#include "loggerCpp/consoleLogSink.hpp"

#include <iostream>
#include <format>

void ConsoleLogSink::write(const utils::LogEvent& event) {
    // Format and output log level, timestamp, message and location
    std::cout << std::format("{}[{}]\n[{}] {}{} (function_name: {} row:{})\n",
        utils::getColorForLogLevel(event.level),
        utils::getLogLevelString(event.level),
        event.timestamp,
        COLOR_RESET,
        event.message,
        event.location.function_name(),
        event.location.line()
       );

}