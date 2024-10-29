#pragma once

#include "utils.hpp"

#include <source_location>
#include <fstream>
#include <string_view>

// Abstract base class for log sinks
class LogSink {
public:
    virtual ~LogSink() noexcept = default;
    virtual void write(const utils::LogEvent& event) = 0;

protected:
    LogSink() noexcept = default;
    LogSink(const LogSink&) = delete;
    LogSink& operator=(const LogSink&) = delete;
    LogSink(LogSink&&) noexcept = default;
    LogSink& operator=(LogSink&&) noexcept = default;
};


