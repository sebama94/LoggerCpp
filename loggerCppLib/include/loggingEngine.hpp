#pragma once

#include "utils.hpp"
#include "logSink.hpp"
#include <memory>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <latch>
#include <semaphore>

// Logger Macros for convenient logging with [[likely]] hints for hot paths
#define LOG_DEBUG(msg) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::DEBUG, msg, std::source_location::current()) 
#define LOG_INFO(msg) [[likely]] LoggingEngine::getInstance().log(utils::LogLevel::INFO, msg, std::source_location::current())
#define LOG_WARN(msg) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::WARNING, msg, std::source_location::current())
#define LOG_ERROR(msg) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::ERROR, msg, std::source_location::current())
#define LOG_CRITICAL(msg) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::CRITICAL, msg, std::source_location::current())

class LoggingEngine {
public:
    [[nodiscard]] static LoggingEngine& getInstance() noexcept;
    static void resetInstance() noexcept;
    
    void setLogLevel(utils::LogLevel level) noexcept;
    void addSink(std::shared_ptr<LogSink> sink, utils::LogLevel level);
    void processEvent(const utils::LogEvent& event) noexcept;
    void log(utils::LogLevel level, const std::string& message, const std::source_location& location) noexcept;

    void startAsync() noexcept;
    void stopAsync() noexcept;

private:
    LoggingEngine();
    ~LoggingEngine() noexcept;
    LoggingEngine(const LoggingEngine&) = delete;
    LoggingEngine& operator=(const LoggingEngine&) = delete;
    LoggingEngine(LoggingEngine&&) = delete;
    LoggingEngine& operator=(LoggingEngine&&) = delete;

    void processEventQueue() noexcept;
    [[nodiscard]] constexpr bool shouldLog(utils::LogLevel eventLevel, utils::LogLevel sinkLevel) const noexcept;

    alignas(64) utils::LogLevel globalLogLevel;
    alignas(64) std::vector<std::pair<std::shared_ptr<LogSink>, utils::LogLevel>> sinks;
    std::mutex sinkMutex;

    alignas(64) std::queue<utils::LogEvent> eventQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    std::binary_semaphore queueSem{0};
    std::atomic<bool> asyncMode{false};
    std::atomic<bool> stopLogging{false}; 
    std::jthread loggingThread;
};
