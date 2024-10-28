#pragma once

#include "utils.hpp"
#include "logSink.hpp"
#include <memory>
#include <mutex>
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>

// Logger Macros for convenient logging
#define LOG_DEBUG(msg) LoggingEngine::getInstance().log(utils::LogLevel::DEBUG, msg, std::source_location::current())
#define LOG_INFO(msg) LoggingEngine::getInstance().log(utils::LogLevel::INFO, msg, std::source_location::current())
#define LOG_WARN(msg) LoggingEngine::getInstance().log(utils::LogLevel::WARNING, msg, std::source_location::current())
#define LOG_ERROR(msg) LoggingEngine::getInstance().log(utils::LogLevel::ERROR, msg, std::source_location::current())
#define LOG_CRITICAL(msg) LoggingEngine::getInstance().log(utils::LogLevel::CRITICAL, msg, std::source_location::current())

class LoggingEngine {
public:
    static LoggingEngine& getInstance();
    static void resetInstance();
    
    void setLogLevel(utils::LogLevel level);
    void addSink(std::shared_ptr<LogSink> sink, utils::LogLevel level);
    void processEvent(const utils::LogEvent& event);
    void log(utils::LogLevel level, const std::string& message, const std::source_location& location);

    void startAsync();
    void stopAsync();

private:
    LoggingEngine();
    ~LoggingEngine();
    LoggingEngine(const LoggingEngine&) = delete;
    LoggingEngine& operator=(const LoggingEngine&) = delete;
    LoggingEngine(LoggingEngine&&) = delete;
    LoggingEngine& operator=(LoggingEngine&&) = delete;

    void processEventQueue();
    bool shouldLog(utils::LogLevel eventLevel, utils::LogLevel sinkLevel);

    utils::LogLevel globalLogLevel;
    std::vector<std::pair<std::shared_ptr<LogSink>, utils::LogLevel>> sinks;
    std::mutex sinkMutex;

    std::queue<utils::LogEvent> eventQueue;
    std::mutex queueMutex;
    std::condition_variable queueCV;
    bool asyncMode;
    bool stopLogging;
    std::thread loggingThread;
};
