# LoggerCpp

A modern C++ logging library providing flexible, thread-safe logging capabilities with multiple output sinks.

## Features

- Thread-safe logging operations
- Multiple output sinks (Console, File, Database*, Network*)
- Configurable log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
- JSON configuration support
- Source location tracking (file, line, function)
- Colorized console output
- Asynchronous logging support
- Header-only core components
- Modern C++20 features

## Architecture

The library is built around several key components:

### LoggingEngine
- Singleton class that manages the logging system
- Handles log event routing to appropriate sinks
- Manages asynchronous logging queue
- Controls global log level filtering

### LogSink Interface
- Abstract base class for all output sinks
- Defines common interface for writing log events
- Implemented by specialized sinks:
  - ConsoleLogSink: Outputs to stdout with color formatting
  - FileLogSink: Writes to specified files
  - DatabaseLogSink: (Planned) Database logging
  - NetworkLogSink: (Planned) Network transmission

### ConfigurationManager
- Handles JSON-based configuration
- Dynamically creates and configures log sinks
- Sets global logging parameters
- Supports hot-reloading of configurations

### Utils
- Provides common utilities and helper functions
- Defines LogEvent structure and LogLevel enum
- Handles timestamp formatting and color coding
- Source location tracking utilities

## Requirements

- C++20 compatible compiler
- nlohmann/json library for configuration parsing
- CMake 3.15 or higher

## Usage

### Basic Example