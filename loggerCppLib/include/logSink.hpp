#pragma once

#include "utils.hpp"

#include <source_location>
#include <fstream>
#include <string_view>

// Abstract base class for log sinks
class LogSink {
public:
    virtual ~LogSink() noexcept = default;
    virtual void write(const utils::LogEvent& message) = 0;

protected:
    LogSink() noexcept = default;
    LogSink(const LogSink&) = delete;
    LogSink& operator=(const LogSink&) = delete;
    LogSink(LogSink&&) noexcept = default;
    LogSink& operator=(LogSink&&) noexcept = default;
};

// Console output sink
class ConsoleLogSink final : public LogSink {
public:
    ConsoleLogSink() noexcept = default;
    void write(const utils::LogEvent& message) override;
};

// File output sink with buffered writes
class FileLogSink final : public LogSink {
public:
    explicit FileLogSink(std::string_view fileName);
    void write(const utils::LogEvent& message) override;

private:
    alignas(64) std::ofstream fileName;
    static constexpr std::size_t BUFFER_SIZE = 8192; // 8KB buffer
};

// Database output sink
class DatabaseLogSink final : public LogSink {
public:
    DatabaseLogSink() noexcept = default;
    void write(const utils::LogEvent& message) override;
};

// Network output sink
class NetworkLogSink final : public LogSink {
public:
    NetworkLogSink() noexcept = default; 
    void write(const utils::LogEvent& message) override;
};