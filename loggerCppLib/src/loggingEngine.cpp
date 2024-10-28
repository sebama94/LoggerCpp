// LoggingEngine.cpp

#include "loggingEngine.hpp"

LoggingEngine& LoggingEngine::getInstance() {
    static LoggingEngine instance;
    return instance;
}

LoggingEngine::LoggingEngine() : globalLogLevel(utils::LogLevel::INFO), asyncMode(false), stopLogging(false) 
{
    startAsync();
}

LoggingEngine::~LoggingEngine() {
    stopAsync();  // Ensure async logging thread stops on destruction
}

void LoggingEngine::setLogLevel(utils::LogLevel level) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    globalLogLevel = level;
}

void LoggingEngine::addSink(std::shared_ptr<LogSink> sink, utils::LogLevel level) {
    std::lock_guard<std::mutex> lock(sinkMutex);
    sinks.emplace_back(sink, level);
}

void LoggingEngine::resetInstance() {
    LoggingEngine::getInstance().~LoggingEngine();
}   

void LoggingEngine::processEvent(const utils::LogEvent& event) {
    if (event.level < globalLogLevel) return;

    if (asyncMode) {
        std::lock_guard<std::mutex> lock(queueMutex);
        eventQueue.push(event);
        queueCV.notify_one();
    } else {
        std::lock_guard<std::mutex> lock(sinkMutex);
        for (const auto& [sink, sinkLevel] : sinks) {
            if (shouldLog(event.level, sinkLevel)) {
                sink->write(event);
            }
        }
    }
}

void LoggingEngine::log(utils::LogLevel level, const std::string& message, const std::source_location& location) {
    utils::LogEvent event{level, message, location};
    processEvent(event);
}

void LoggingEngine::startAsync() {
    std::lock_guard<std::mutex> lock(queueMutex);
    if (!asyncMode) {
        asyncMode = true;
        stopLogging = false;
        loggingThread = std::thread(&LoggingEngine::processEventQueue, this);
    }
}

void LoggingEngine::stopAsync() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        if (!asyncMode) return;
        stopLogging = true;
        queueCV.notify_one();
    }
    if (loggingThread.joinable()) {
        loggingThread.join();
    }
    asyncMode = false;
}

void LoggingEngine::processEventQueue() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCV.wait(lock, [this]() { return !eventQueue.empty() || stopLogging; });

        if (stopLogging && eventQueue.empty()) break;

        while (!eventQueue.empty()) {
            auto event = eventQueue.front();
            eventQueue.pop();

            lock.unlock();
            {
                std::lock_guard<std::mutex> sinkLock(sinkMutex);
                for (const auto& [sink, sinkLevel] : sinks) {
                    if (shouldLog(event.level, sinkLevel)) {
                        sink->write(event);
                    }
                }
            }
            lock.lock();
        }
    }
}

bool LoggingEngine::shouldLog(utils::LogLevel eventLevel, utils::LogLevel sinkLevel) {
    return eventLevel >= sinkLevel;
}
