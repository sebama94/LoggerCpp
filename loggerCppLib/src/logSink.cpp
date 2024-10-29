#include "logSink.hpp"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <format>

void ConsoleLogSink::write(const utils::LogEvent& event) {
    // Format and output log level, timestamp, message and location
    std::cout << std::format("{} [{}] {} ({}:{}:{})\n{} [{}] {} {}\n",
        utils::getColorForLogLevel(event.level),
        utils::getLogLevelString(event.level),
        COLOR_RESET,
        event.location.file_name(),
        event.location.line(),
        event.location.function_name(),
        utils::getColorForLogLevel(event.level), 
        event.timestamp,
        COLOR_RESET,
        event.message);
}

FileLogSink::FileLogSink(std::string_view name) : fileName(std::string(name), std::ios::app | std::ios::binary) {
    if (!fileName.is_open()) {
        throw std::runtime_error(std::format("Failed to open log file: {}", name));
    }
    fileName.rdbuf()->pubsetbuf(nullptr, 0); // Disable buffering for immediate writes
}

void FileLogSink::write(const utils::LogEvent& event) {
    if (!fileName.is_open()) {
        std::cerr << "Error: Log file not found or cannot be opened\n";
        return;
    }

    // Use std::format for more efficient string formatting
    fileName << std::format("[{}] ({}:{}:{})\n[{}] {}\n", 
        utils::getLogLevelString(event.level),
        event.location.file_name(),
        event.location.line(),
        event.location.function_name(),
        event.timestamp,
        event.message);
}

void DatabaseLogSink::write(const utils::LogEvent& event) {
    // TODO: Implement database logging
    // This would connect to a database and insert log records
    std::cerr << "Error: Database logging not implemented\n";
    throw std::runtime_error("Database logging not implemented");
}

void NetworkLogSink::write(const utils::LogEvent& event) {
    // TODO: Implement network logging
    // This would send logs to a remote logging service
    std::cerr << "Error: Network logging not implemented\n";
    throw std::runtime_error("Network logging not implemented");
}
