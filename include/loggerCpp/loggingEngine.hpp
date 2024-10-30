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
#include "logEventRouter.hpp"





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

    alignas(64) LogEventRouter router;                                                       ///< Event router for log messages
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
