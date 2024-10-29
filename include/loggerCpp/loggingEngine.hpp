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


// Logger Macros for convenient logging with [[likely]] hints for hot paths
#define LOG_DEBUG(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::DEBUG, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_INFO(msg, ...) [[likely]] LoggingEngine::getInstance().log(utils::LogLevel::INFO, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_WARN(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::WARNING, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_ERROR(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::ERROR, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))
#define LOG_CRITICAL(msg, ...) [[unlikely]] LoggingEngine::getInstance().log(utils::LogLevel::CRITICAL, std::source_location::current(), fmt::format(msg, ##__VA_ARGS__))

class LoggingEngine {
public:
    [[nodiscard]] static LoggingEngine& getInstance() noexcept;
    static void resetInstance() noexcept;
    
    void setLogLevel(utils::LogLevel level) noexcept;
    void addSink(std::shared_ptr<LogSink> sink, utils::LogLevel level);
    void processEvent(const utils::LogEvent& event) noexcept;
    template<typename... Args>
    void log(utils::LogLevel level, const std::source_location& location, const std::string& fmt, Args&&... args) noexcept {
        std::string formattedMessage = fmt::vformat(fmt, fmt::make_format_args(std::forward<Args>(args)...));
        utils::LogEvent event{level, formattedMessage, location};
        processEvent(std::move(event));
    }


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
