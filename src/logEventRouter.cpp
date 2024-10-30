#include "loggerCpp/logEventRouter.hpp"
#include "loggerCpp/logSink.hpp"

// Remove unnecessary constructor/destructor since we use =default in header
void LogEventRouter::setLogLevel(utils::LogLevel level) noexcept {
    currentLogLevel = level;
}

void LogEventRouter::addRoute(utils::LogLevel level, std::shared_ptr<LogSink> sink) noexcept {
    routes[level].push_back(std::move(sink));
}

void LogEventRouter::routeEvent(const utils::LogEvent& event) noexcept {
    // Use [[likely]] hint since most events should be at or above current level
    if (event.level >= currentLogLevel) [[likely]] {
        // Use contains() for cleaner check (C++23)
        if (routes.contains(event.level)) [[likely]] {
            for (const auto& sink : routes[event.level]) {
                sink->write(event);
            }
        }
    }
}