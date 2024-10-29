#include "configurationManager.hpp"
#include "logSink.hpp"
#include <fstream>
#include <expected>

ConfigurationManager::ConfigurationManager(std::string_view configFilePath) : configFilePath(configFilePath) {
    std::ifstream file(std::string(configFilePath), std::ios::binary); // Binary mode for faster reading
    if (!file.is_open()) [[unlikely]] {
        throw std::runtime_error("Failed to open configuration file");
    }
    
    // Pre-allocate buffer for faster parsing
    file.seekg(0, std::ios::end);
    const auto size = file.tellg();
    file.seekg(0);
    std::string buffer(size, '\0');
    file.read(buffer.data(), size);
    
    config = json::parse(buffer, nullptr, false, true); // Allow comments, faster parsing
    LoggingEngine& logger = LoggingEngine::getInstance();
    applyConfiguration(logger);
}

void ConfigurationManager::applyConfiguration(LoggingEngine& logger) {
    if (config.is_null()) [[unlikely]] {
        throw std::runtime_error("Configuration is null");
    }

    // Set log level
    if (const auto it = config.find("logLevel"); it != config.end()) {
        const auto logLevelStr = it->get<std::string>();
        utils::LogLevel level = utils::stringToLogLevel(logLevelStr);
        logger.setLogLevel(level);
    }

    // Set sinks
    if (const auto it = config.find("sinks"); it != config.end()) {
        const auto& sinks = *it;
        for (const auto& sink : sinks) {
            const auto type = sink["type"].get<std::string>();
            const auto levelStr = sink["level"].get<std::string>();
            
            utils::LogLevel level = utils::stringToLogLevel(levelStr);

            if (type == "console") [[likely]] {
                logger.addSink(std::make_shared<ConsoleLogSink>(), level);
            } else if (type == "file") {
                const auto filename = sink["filename"].get<std::string>();
                logger.addSink(std::make_shared<FileLogSink>(filename), level);
            } else [[unlikely]] {
                throw std::runtime_error("Invalid sink type in configuration");
            }
        }
    }
}