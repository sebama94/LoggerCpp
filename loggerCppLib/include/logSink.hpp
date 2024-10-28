#pragma once

#include "utils.hpp"

#include <source_location>
#include <fstream>

class LogSink {
public:
    virtual ~LogSink() = default;
    virtual void write(const utils::LogEvent& message) = 0;

protected:
    LogSink() = default;
};

class ConsoleLogSink : public LogSink {
public:
    void write(const utils::LogEvent& message) override;

};  

class FileLogSink : public LogSink {
public:
    FileLogSink(std::string fileName);
    void write(const utils::LogEvent& message) override;

private:
    std::ofstream fileName;
};

class DatabaseLogSink : public LogSink {
public:
    void write(const utils::LogEvent& message) override;
};

class NetworkLogSink : public LogSink {
public:
    void write(const utils::LogEvent& message) override;
};