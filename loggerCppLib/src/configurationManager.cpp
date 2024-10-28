#include "configurationManager.hpp"
#include "logSink.hpp"

ConfigurationManager::ConfigurationManager(const std::string& configFilePath) : configFilePath(configFilePath) {
    std::ifstream file(configFilePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file");
    }
    config = json::parse(file);
    LoggingEngine& logger = LoggingEngine::getInstance();
    applyConfiguration(logger);
}

void ConfigurationManager::applyConfiguration(LoggingEngine& logger) {
    if (config.is_null()) {
        throw std::runtime_error("Configuration is null");
    }

    // Set log level
    if (config.contains("logLevel")) {
        std::string logLevelStr = config["logLevel"].get<std::string>();
        utils::LogLevel level = utils::stringToLogLevel(logLevelStr);
        logger.setLogLevel(level);
    }

    // Set sinks
    if (config.contains("sinks")) {
        for (const auto& sink : config["sinks"]) {
            std::string type = sink["type"].get<std::string>();
            std::string levelStr = sink["level"].get<std::string>();
            
            utils::LogLevel level = utils::stringToLogLevel(levelStr);

            if (type == "console") {
                logger.addSink(std::make_shared<ConsoleLogSink>(), level);
            } else if (type == "file") {
                std::string filename = sink["filename"].get<std::string>();
                logger.addSink(std::make_shared<FileLogSink>(filename), level);
            } else {
                throw std::runtime_error("Invalid sink type in configuration");
            }
        }
    }
}

ConfigurationManager::~ConfigurationManager() {
    //LoggingEngine::resetInstance();
}