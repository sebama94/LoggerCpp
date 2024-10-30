#include "loggerCpp/configurationManager.hpp"
#include "loggerCpp/consoleLogSink.hpp"
#include "loggerCpp/fileLogSink.hpp"
#include "loggerCpp/dataBaseLogSink.hpp"
#include "loggerCpp/networkLogSink.hpp"

#include <fstream>
#include <expected>


ConfigurationManager::ConfigurationManager(utils::LogLevel logLevel) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.setLogLevel(logLevel);
}

void ConfigurationManager::applyConsoleSink(const utils::LogLevel& level) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<ConsoleLogSink>(), level);
}

void ConfigurationManager::applyFileSink(const utils::LogLevel& level, const std::string_view& filename) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<FileLogSink>(filename), level);
}

void ConfigurationManager::applyNetworkSink(const utils::LogLevel& level, const std::string_view& url) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<NetworkLogSink>(), level);
}

void ConfigurationManager::applyDataBaseSink(const utils::LogLevel& level, const std::string_view& database) {    
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<DataBaseLogSink>(), level);
}

