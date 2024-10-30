#pragma once

#include "logSink.hpp"  


// Database output sink
class DataBaseLogSink final : public LogSink {
public:
    DataBaseLogSink() noexcept = default;
    void write(const utils::LogEvent& event) override;
};