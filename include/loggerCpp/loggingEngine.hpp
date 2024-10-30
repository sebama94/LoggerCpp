#pragma once

#include "utils.hpp"
#include "logSink.hpp"
#include <fmt/format.h>
#include <memory>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <latch>
#include <semaphore>
#include <source_location>

/**
 * @file loggingEngine.hpp
 * @brief Core logging engine implementation providing logging functionality
 */

/**
 * @def LOG_DEBUG(msg, ...)
 * @brief Macro for logging a debug message
 * @param msg The message to log
 * @param ... The arguments to format into the message
 */
#define LOG_DEBUG(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::DEBUG, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))

/**
 * @def LOG_INFO(msg, ...)
 * @brief Macro for logging an info message
 * @param msg The message to log
 * @param ... The arguments to format into the message
 */
#define LOG_INFO(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::INFO, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))

/**
 * @def LOG_WARN(msg, ...)
 * @brief Macro for logging a warning message
 * @param msg The message to log
 * @param ... The arguments to format into the message
 */
#define LOG_WARN(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::WARNING, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))

/**
 * @def LOG_ERROR(msg, ...)
 * @brief Macro for logging an error message
 * @param msg The message to log
 * @param ... The arguments to format into the message
 */
#define LOG_ERROR(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::ERROR, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))

/**
 * @def LOG_CRITICAL(msg, ...)
 * @brief Macro for logging a critical message
 * @param msg The message to log
 * @param ... The arguments to format into the message
 */
#define LOG_CRITICAL(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::CRITICAL, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))

/**
 * @class LoggingEngine
 * @brief Core logging engine class implementing singleton pattern
 *
 * This class provides the core logging functionality including:
 * - Singleton access to logging services
 * - Multiple sink support for different logging destinations
 * - Asynchronous logging capabilities
 * - Log level filtering
 * - Thread-safe logging operations
 */
class LoggingEngine {
public:
    /**
     * @brief Get the singleton instance of LoggingEngine
     * @return Reference to the singleton LoggingEngine instance
     */
    [[nodiscard]] static LoggingEngine& getInstance() noexcept;

    /**
     * @brief Reset the singleton instance of LoggingEngine
     */
    static void resetInstance() noexcept;
    
    /**
     * @brief Set the global log level for the logger
     * @param level The log level to set
     */
    void setLogLevel(utils::LogLevel level) noexcept;

    /**
     * @brief Add a logging sink with associated level
     * @param sink Smart pointer to the sink implementation
     * @param level Minimum log level for this sink
     */
    void addSink(std::shared_ptr<LogSink> sink, utils::LogLevel level);

    /**
     * @brief Process a logging event
     * @param event The event to process
     */
    void processEvent(const utils::LogEvent& event) noexcept;

    /**
     * @brief Log a message with formatting
     * @param level The log level for this message
     * @param location Source code location information
     * @param fmt Format string
     * @param args Arguments to format into the message
     */
    template<typename... Args>
    void log(utils::LogLevel level, const std::source_location& location, const std::string& fmt, Args&&... args) noexcept {
        std::string formattedMessage = fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...));
        utils::LogEvent event{level, formattedMessage, location};
        processEvent(std::move(event));
    }

    /**
     * @brief Enable asynchronous logging mode
     */
    void startAsync() noexcept;

    /**
     * @brief Disable asynchronous logging mode
     */
    void stopAsync() noexcept;

private:
    /**
     * @brief Default constructor - private for singleton pattern
     */
    LoggingEngine();

    /**
     * @brief Destructor - private for singleton pattern
     */
    ~LoggingEngine() noexcept;

    // Delete copy/move operations for singleton pattern
    LoggingEngine(const LoggingEngine&) = delete;
    LoggingEngine& operator=(const LoggingEngine&) = delete;
    LoggingEngine(LoggingEngine&&) = delete;
    LoggingEngine& operator=(LoggingEngine&&) = delete;

    /**
     * @brief Process events in the queue
     */
    void processEventQueue() noexcept;

    /**
     * @brief Check if a log event should be processed
     * @param eventLevel Log level of the event
     * @param sinkLevel Log level of the sink
     * @return true if event should be logged, false otherwise
     */
    [[nodiscard]] constexpr bool shouldLog(utils::LogLevel eventLevel, utils::LogLevel sinkLevel) const noexcept;

    alignas(64) utils::LogLevel globalLogLevel;                                              ///< Global minimum log level
    alignas(64) std::vector<std::pair<std::shared_ptr<LogSink>, utils::LogLevel>> sinks;    ///< Logging sinks with levels
    std::mutex sinkMutex;                                                                    ///< Mutex for sink operations
    alignas(64) std::queue<utils::LogEvent> eventQueue;                                      ///< Queue for async logging
    std::mutex queueMutex;                                                                   ///< Mutex for queue operations
    std::condition_variable queueCV;                                                         ///< Condition for queue processing
    std::binary_semaphore queueSem{0};                                                      ///< Semaphore for queue signaling
    std::atomic<bool> asyncMode{false};                                                      ///< Flag for async mode
    std::atomic<bool> stopLogging{false};                                                    ///< Flag to stop logging
    std::jthread loggingThread;                                                             ///< Thread for async logging
};
