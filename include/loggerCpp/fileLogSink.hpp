#pragma once

#include "logSink.hpp"

#include <string_view>
#include <fstream>

/**
 * @brief File output sink for logging with buffered writes
 * 
 * This class implements a logging sink that writes log messages to a file.
 * It inherits from the LogSink base class and provides file-specific logging functionality
 * with buffered writes for improved performance.
 */
class FileLogSink final : public LogSink {
public:
    /**
     * @brief Constructs a FileLogSink with the specified file name
     * 
     * @param fileName The name/path of the file to write logs to
     */
    explicit FileLogSink(std::string_view fileName);

    /**
     * @brief Writes a log event to the file
     * 
     * @param event The log event containing the message and metadata to be written
     * @throws std::runtime_error if file write fails
     * 
     * This function formats and writes the provided log event to the configured file
     * using buffered writes for better performance.
     */
    void write(const utils::LogEvent& event) override;

private:
    alignas(64) std::ofstream fileName;  /**< Output file stream with cache line alignment */
    static constexpr std::size_t BUFFER_SIZE = 8192; /**< Size of write buffer in bytes (8KB) */
};