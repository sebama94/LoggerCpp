#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <source_location>

/**
 * @brief ANSI color codes for console output formatting
 */
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_WHITE   "\033[37m"

#define LOG_DEBUG(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::DEBUG, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_INFO(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::INFO, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_WARNING(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::WARNING, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_ERROR(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::ERROR, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__)) 
#define LOG_CRITICAL(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::CRITICAL, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_TRACE(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::TRACE, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))



namespace utils {

    /**
     * @brief Enumeration of available log levels
     */
    enum class LogLevel : uint8_t {
        DEBUG,      /**< Debug level for detailed debugging information */
        INFO,       /**< Info level for general information messages */
        WARNING,    /**< Warning level for potential issues */
        ERROR,      /**< Error level for error conditions */
        CRITICAL,   /**< Critical level for critical failures */
        TRACE,      /**< Trace level for very detailed debugging */
        NONE        /**< No logging */
    };

    /**
     * @brief Enumeration of available sink types
     */
    enum class SinkType : uint8_t {
        CONSOLE,    /**< Console output sink */
        FILE,       /**< File output sink */
        NETWORK,    /**< Network output sink */
        DATABASE    /**< Database output sink */
    };

    /**
     * @brief Get the ANSI color code for a given log level
     * @param level The log level to get the color for
     * @return String containing the ANSI color code
     */
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

    /**
     * @brief Convert a log level to its string representation
     * @param level The log level to convert
     * @return String representation of the log level
     */
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
            default: return "NONE";
        }   
    };

    /**
     * @brief Convert a string to its corresponding log level
     * @param levelString String representation of the log level
     * @return Corresponding LogLevel enum value
     */
    static LogLevel stringToLogLevel(const std::string& levelString) noexcept
    {
        // TODO: Implement this 
        if (levelString == "DEBUG") return LogLevel::DEBUG;
        if (levelString == "INFO") return LogLevel::INFO;
        if (levelString == "WARNING") return LogLevel::WARNING;
        if (levelString == "ERROR") return LogLevel::ERROR;
        if (levelString == "CRITICAL") return LogLevel::CRITICAL;
        if (levelString == "TRACE") return LogLevel::TRACE;
        return LogLevel::NONE;
    }

    /**
     * @brief Structure representing a log event
     */
    struct LogEvent {
        LogLevel level;                 /**< Log level of the event */
        std::string message;            /**< Log message content */
        std::string timestamp;          /**< Timestamp of when the event occurred */
        std::source_location location;  /**< Source code location information */

        /**
         * @brief Construct a new Log Event
         * @param level Log level for the event
         * @param message Message content
         * @param location Source location information
         */
        LogEvent(LogLevel level, std::string message, std::source_location location)
            : level(level), message(message), timestamp(getTimestamp()), location(location) {}   

        private:
            /**
             * @brief Get current timestamp as formatted string
             * @return Formatted timestamp string
             */
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
