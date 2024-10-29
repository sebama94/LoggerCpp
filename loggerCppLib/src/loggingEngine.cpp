// LoggingEngine.cpp

#include "loggingEngine.hpp"
#include <memory>
#include <latch>
#include <semaphore>

LoggingEngine& LoggingEngine::getInstance() noexcept {
    static LoggingEngine instance;
    return instance;
}

LoggingEngine::LoggingEngine() : globalLogLevel(utils::LogLevel::INFO), asyncMode(false), stopLogging(false) 
{
    startAsync();
}

LoggingEngine::~LoggingEngine() noexcept {
    stopAsync();  // Ensure async logging thread stops on destruction
}

void LoggingEngine::setLogLevel(utils::LogLevel level) noexcept {
    std::lock_guard lock(sinkMutex);
    globalLogLevel = level;
}

void LoggingEngine::addSink(std::shared_ptr<LogSink> sink, utils::LogLevel level) {
    std::lock_guard lock(sinkMutex);
    sinks.emplace_back(std::move(sink), level);
}

void LoggingEngine::resetInstance() noexcept {
    LoggingEngine::getInstance().~LoggingEngine();
}   

void LoggingEngine::processEvent(const utils::LogEvent& event) noexcept {
    if (event.level < globalLogLevel) [[unlikely]] return;

    if (asyncMode) {
        std::lock_guard lock(queueMutex);
        eventQueue.push(std::move(event));
        queueCV.notify_one();
    } else {
        std::lock_guard lock(sinkMutex);
        for (const auto& [sink, sinkLevel] : sinks) {
            if (shouldLog(event.level, sinkLevel)) [[likely]] {
                sink->write(event);
            }
        }
    }
}

void LoggingEngine::log(utils::LogLevel level, const std::string& message, const std::source_location& location) noexcept {
    utils::LogEvent event{level, message, location};
    processEvent(std::move(event));
}

void LoggingEngine::startAsync() noexcept {
    std::lock_guard lock(queueMutex);
    if (!asyncMode) {
        asyncMode = true;
        stopLogging = false;
        loggingThread = std::jthread([this](std::stop_token stoken) {
            processEventQueue();
        });
    }
}

void LoggingEngine::stopAsync() noexcept {
    {
        std::lock_guard lock(queueMutex);
        if (!asyncMode) return;
        stopLogging = true;
        queueCV.notify_one();
    }
    if (loggingThread.joinable()) {
        loggingThread.join();
    }
    asyncMode = false;
}

void LoggingEngine::processEventQueue() noexcept {
    while (true) {
        std::unique_lock lock(queueMutex);
        queueCV.wait(lock, [this]() { return !eventQueue.empty() || stopLogging; });

        if (stopLogging && eventQueue.empty()) [[unlikely]] break;

        while (!eventQueue.empty()) {
            auto event = std::move(eventQueue.front());
            eventQueue.pop();

            lock.unlock();
            {
                std::lock_guard sinkLock(sinkMutex);
                for (const auto& [sink, sinkLevel] : sinks) {
                    if (shouldLog(event.level, sinkLevel)) [[likely]] {
                        sink->write(event);
                    }
                }
            }
            lock.lock();
        }
    }
}

[[nodiscard]] constexpr bool LoggingEngine::shouldLog(utils::LogLevel eventLevel, utils::LogLevel sinkLevel) const noexcept {
    return eventLevel >= sinkLevel;
}
