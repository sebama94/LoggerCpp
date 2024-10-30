#include "loggerCpp/configurationManager.hpp"
#include "loggerCpp/consoleLogSink.hpp"
#include "loggerCpp/fileLogSink.hpp"
#include "loggerCpp/dataBaseLogSink.hpp"
#include "loggerCpp/networkLogSink.hpp"

#include <fstream>
#include <vector>

ConfigurationManager::ConfigurationManager(utils::LogLevel logLevel) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.setLogLevel(logLevel);
}

void ConfigurationManager::applyConsoleSink(const utils::LogLevel level) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<ConsoleLogSink>(), level);
}

void ConfigurationManager::applyConsoleSink(const utils::LogLevel level1, const utils::LogLevel level2) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<ConsoleLogSink>(), level1);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level2);
}

void ConfigurationManager::applyConsoleSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<ConsoleLogSink>(), level1);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level2);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level3);
}

void ConfigurationManager::applyConsoleSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<ConsoleLogSink>(), level1);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level2);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level3);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level4);
}

void ConfigurationManager::applyConsoleSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const utils::LogLevel level5) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<ConsoleLogSink>(), level1);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level2);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level3);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level4);
    logger.addSink(std::make_shared<ConsoleLogSink>(), level5);
}

void ConfigurationManager::applyFileSink(const utils::LogLevel level, const std::string_view& filename) {  
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<FileLogSink>(filename), level);
}

void ConfigurationManager::applyFileSink(const utils::LogLevel level1, const utils::LogLevel level2, const std::string_view& filename) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<FileLogSink>(filename), level1);
    logger.addSink(std::make_shared<FileLogSink>(filename), level2);
}

void ConfigurationManager::applyFileSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const std::string_view& filename) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<FileLogSink>(filename), level1);
    logger.addSink(std::make_shared<FileLogSink>(filename), level2);
    logger.addSink(std::make_shared<FileLogSink>(filename), level3);
}

void ConfigurationManager::applyFileSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const std::string_view& filename) {    
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<FileLogSink>(filename), level1);
    logger.addSink(std::make_shared<FileLogSink>(filename), level2);
    logger.addSink(std::make_shared<FileLogSink>(filename), level3);
    logger.addSink(std::make_shared<FileLogSink>(filename), level4);
}

void ConfigurationManager::applyFileSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const utils::LogLevel level5, const std::string_view& filename) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<FileLogSink>(filename), level1);
    logger.addSink(std::make_shared<FileLogSink>(filename), level2);
    logger.addSink(std::make_shared<FileLogSink>(filename), level3);
    logger.addSink(std::make_shared<FileLogSink>(filename), level4);
    logger.addSink(std::make_shared<FileLogSink>(filename), level5);
}

void ConfigurationManager::applyNetworkSink(const utils::LogLevel level, const std::string_view& url) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<NetworkLogSink>(url), level);
}

void ConfigurationManager::applyNetworkSink(const utils::LogLevel level1, const utils::LogLevel level2, const std::string_view& url) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<NetworkLogSink>(url), level1);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level2);
}

void ConfigurationManager::applyNetworkSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const std::string_view& url) { 
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<NetworkLogSink>(url), level1);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level2);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level3);
}

void ConfigurationManager::applyNetworkSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const std::string_view& url) {          
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<NetworkLogSink>(url), level1);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level2);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level3);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level4);
}

void ConfigurationManager::applyNetworkSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const utils::LogLevel level5, const std::string_view& url) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<NetworkLogSink>(url), level1);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level2);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level3);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level4);
    logger.addSink(std::make_shared<NetworkLogSink>(url), level5);
}

void ConfigurationManager::applyDataBaseSink(const utils::LogLevel level, const std::string_view& database) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level);
}

void ConfigurationManager::applyDataBaseSink(const utils::LogLevel level1, const utils::LogLevel level2, const std::string_view& database) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level1);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level2);
}

void ConfigurationManager::applyDataBaseSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const std::string_view& database) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level1);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level2);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level3);
}

void ConfigurationManager::applyDataBaseSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const std::string_view& database) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level1);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level2);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level3);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level4);
}

void ConfigurationManager::applyDataBaseSink(const utils::LogLevel level1, const utils::LogLevel level2, const utils::LogLevel level3, const utils::LogLevel level4, const utils::LogLevel level5, const std::string_view& database) {
    LoggingEngine& logger = LoggingEngine::getInstance();
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level1);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level2);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level3);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level4);
    logger.addSink(std::make_shared<DataBaseLogSink>(database), level5);
}