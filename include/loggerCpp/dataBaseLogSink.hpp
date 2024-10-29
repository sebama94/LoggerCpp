#pragma once

#include "logSink.hpp"  


// Database output sink
class DatabaseLogSink final : public LogSink {
public:
    DatabaseLogSink() noexcept = default;
    void write(const utils::LogEvent& event) override;
};