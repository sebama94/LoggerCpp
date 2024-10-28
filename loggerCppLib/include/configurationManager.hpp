#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "loggingEngine.hpp"

using json = nlohmann::json;

class ConfigurationManager {
public:
    ConfigurationManager() = default;
    ~ConfigurationManager();

    ConfigurationManager(const std::string& configFilePath);
    void applyConfiguration(LoggingEngine& logger);

private:
    json config;
    std::string configFilePath;
};