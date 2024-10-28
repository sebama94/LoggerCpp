#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <source_location>

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

namespace utils {

    enum class LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL,
        TRACE,
        ALL,
        NONE
    };

    static std::string getColorForLogLevel(LogLevel level) {
        switch (level) {
            case LogLevel::DEBUG: return COLOR_CYAN;
            case LogLevel::INFO: return COLOR_GREEN;
            case LogLevel::WARNING: return COLOR_YELLOW;
            case LogLevel::ERROR: return COLOR_RED;
            case LogLevel::CRITICAL: return COLOR_MAGENTA;
            case LogLevel::TRACE: return COLOR_WHITE;
            default: return COLOR_RESET;
        }
    };

    static std::string getLogLevelString(LogLevel level) noexcept
    {
        switch (level)
        {
            case LogLevel::DEBUG: return "DEBUG";
            case LogLevel::INFO: return "INFO";
            case LogLevel::WARNING: return "WARNING";
            case LogLevel::ERROR: return "ERROR";
            case LogLevel::CRITICAL: return "CRITICAL";
            case LogLevel::TRACE: return "TRACE";
            case LogLevel::ALL: return "ALL";   
            case LogLevel::NONE: return "NONE";
        }   
        return std::string();
    };

    static LogLevel stringToLogLevel(const std::string& levelString) noexcept
    {
        // TODO: Implement this 
        if (levelString == "DEBUG") return LogLevel::DEBUG;
        if (levelString == "INFO") return LogLevel::INFO;
        if (levelString == "WARNING") return LogLevel::WARNING;
        if (levelString == "ERROR") return LogLevel::ERROR;
        if (levelString == "CRITICAL") return LogLevel::CRITICAL;
        if (levelString == "TRACE") return LogLevel::TRACE;
        if (levelString == "ALL") return LogLevel::ALL;
        if (levelString == "NONE") return LogLevel::NONE;
        return LogLevel::NONE;
        
    }

    struct LogEvent {
        LogLevel level;
        std::string message;
        std::string timestamp;  // Change to std::string
        std::source_location location;

        LogEvent(LogLevel level, std::string message, std::source_location location)
            : level(level), message(message), timestamp(getTimestamp()), location(location) {}   

        private:
            std::string getTimestamp() noexcept
            {
                auto now = std::chrono::system_clock::now();
                auto in_time_t = std::chrono::system_clock::to_time_t(now);
                std::stringstream ss;
                ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
                return ss.str();
            }; 
    };
};
