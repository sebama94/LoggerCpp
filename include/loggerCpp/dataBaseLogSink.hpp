#pragma once

#include "logSink.hpp"  

/**
 * @brief Database output sink for logging
 * 
 * This class implements a logging sink that writes log messages to a database.
 * It inherits from the LogSink base class and provides database-specific logging functionality.
 */
class DataBaseLogSink final : public LogSink {
public:
    /**
     * @brief Default constructor
     * 
     * Constructs a DataBaseLogSink object that can write log messages to a database.
     */
    DataBaseLogSink() noexcept = default;   

    /**
     * @brief Constructor with database name
     * 
     * Constructs a DataBaseLogSink object that can write log messages to a database.
     */
    DataBaseLogSink(const std::string_view& database);

    /**
     * @brief Writes a log event to the database
     * 
     * @param event The log event containing the message and metadata to be written
     * @throws None This function is noexcept
     * 
     * This function formats and writes the provided log event to the configured database.
     */
    void write(const utils::LogEvent& event) override;
};