#pragma once

#include "utils.hpp" 
#include <unordered_map>

class LogSink;

class LogEventRouter {
public:
    LogEventRouter();
    ~LogEventRouter();

    void addRoute(utils::LogLevel level, std::shared_ptr<LogSink> sink);
    void setLogLevel(utils::LogLevel level);
    void routeEvent(const utils::LogEvent& message);

private:
    std::unordered_map<utils::LogLevel, std::shared_ptr<LogSink>> routes;
    utils::LogLevel currentLogLevel{utils::LogLevel::INFO};
};