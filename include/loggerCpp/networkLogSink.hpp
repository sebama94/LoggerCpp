#pragma once

#include "logSink.hpp"

/**
 * @brief Network output sink for logging
 * 
 * This class implements a logging sink that writes log messages to a network destination.
 * It inherits from the LogSink base class and provides network-specific logging functionality.
 */
class NetworkLogSink final : public LogSink {
public:
    /**
     * @brief Default constructor
     * 
     * Constructs a NetworkLogSink object that can write log messages to a network destination.
     */
    NetworkLogSink() noexcept = default;

    /**
     * @brief Constructor with URL
     * 
     * Constructs a NetworkLogSink object that can write log messages to a network destination.
     */
    NetworkLogSink(const std::string_view& url);

    /**
     * @brief Writes a log event to the network destination
     * 
     * @param event The log event containing the message and metadata to be written
     * @throws None This function is noexcept
     * 
     * This function formats and writes the provided log event to the configured network destination.
     */
    void write(const utils::LogEvent& event) override;
};