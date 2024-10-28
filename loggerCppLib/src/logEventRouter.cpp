#include "logEventRouter.hpp"
#include "logSink.hpp"

LogEventRouter::LogEventRouter(){}

LogEventRouter::~LogEventRouter(){} 

void LogEventRouter::setLogLevel(utils::LogLevel level) {
    currentLogLevel = level;
}

void LogEventRouter::addRoute(utils::LogLevel level, std::shared_ptr<LogSink> sink) {
    routes[level] = std::move(sink);
}

void LogEventRouter::routeEvent(const utils::LogEvent& event) {
    if (event.level < currentLogLevel) {
        return;
    }

    if (auto it = routes.find(event.level); it != routes.end()) {
        it->second->write(event);
    }
}
