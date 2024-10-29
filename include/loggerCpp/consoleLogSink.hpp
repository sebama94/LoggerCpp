#pragma once

#include "logSink.hpp"

#include <string_view>
#include <fstream>

// Console output sink
class ConsoleLogSink final : public LogSink {
public:
    ConsoleLogSink() noexcept = default;
    void write(const utils::LogEvent& event) override;
};
