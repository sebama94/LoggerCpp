#pragma once

#include "logSink.hpp"

#include <string_view>
#include <fstream>

// File output sink with buffered writes
class FileLogSink final : public LogSink {
public:
    explicit FileLogSink(std::string_view fileName);
    void write(const utils::LogEvent& event) override;

private:
    alignas(64) std::ofstream fileName;
    static constexpr std::size_t BUFFER_SIZE = 8192; // 8KB buffer
};