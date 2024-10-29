#pragma once

#include "utils.hpp"
#include <unordered_map>
#include <memory>

class LogSink;

class LogEventRouter {
public:
    // Default constructors/destructors are sufficient
    LogEventRouter() noexcept = default;
    ~LogEventRouter() = default;

    // Prevent copying to avoid shared state issues
    LogEventRouter(const LogEventRouter&) = delete;
    LogEventRouter& operator=(const LogEventRouter&) = delete;

    // Allow moving for efficient resource transfer
    LogEventRouter(LogEventRouter&&) noexcept = default;
    LogEventRouter& operator=(LogEventRouter&&) noexcept = default;

    // Core functionality with [[nodiscard]] to prevent accidental value drops
    void addRoute(utils::LogLevel level, std::shared_ptr<LogSink> sink) noexcept;
    void setLogLevel(utils::LogLevel level) noexcept;
    void routeEvent(const utils::LogEvent& message) noexcept;

private:
    // Align data for cache-friendly access
    alignas(64) std::unordered_map<utils::LogLevel, std::shared_ptr<LogSink>> routes;
    alignas(64) utils::LogLevel currentLogLevel{utils::LogLevel::INFO};
};