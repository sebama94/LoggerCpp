#include "loggerCpp/fileLogSink.hpp"

void FileLogSink::write(const utils::LogEvent& event) {
    if (!fileName.is_open()) {
        std::cerr << "Error: Log file not found or cannot be opened\n";
        return;
    }

    // Use std::format for more efficient string formatting
    fileName << std::format("[{}] ({}:{})\n[{}] {}\n", 
        utils::getLogLevelString(event.level),
       // event.location.file_name(),
        event.location.function_name(),
        event.location.line(),
        event.timestamp,
        event.message);
}


FileLogSink::FileLogSink(std::string_view name) : fileName(std::string(name), std::ios::app | std::ios::binary) {
    if (!fileName.is_open()) {
        throw std::runtime_error(std::format("Failed to open log file: {}", name));
    }
    fileName.rdbuf()->pubsetbuf(nullptr, 0); // Disable buffering for immediate writes
}

