#pragma once

#include "logSink.hpp"


// Network output sink
class NetworkLogSink final : public LogSink {
public:
    NetworkLogSink() noexcept = default; 
    void write(const utils::LogEvent& event) override;
};