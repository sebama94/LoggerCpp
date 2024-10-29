#pragma once
#include <string>
#include <string_view>
#include <nlohmann/json.hpp>
#include "loggingEngine.hpp"

using json = nlohmann::json;

class ConfigurationManager {
public:
    ConfigurationManager() = default;
    ~ConfigurationManager() noexcept = default;

    // Prevent copying to avoid unnecessary allocations
    ConfigurationManager(const ConfigurationManager&) = delete;
    ConfigurationManager& operator=(const ConfigurationManager&) = delete;
    
    // Allow moving for efficient resource transfer
    ConfigurationManager(ConfigurationManager&&) noexcept = default;
    ConfigurationManager& operator=(ConfigurationManager&&) noexcept = default;

    // Use string_view for more efficient string passing
    explicit ConfigurationManager(std::string_view configFilePath);
    
    void applyConfiguration(LoggingEngine& logger);

private:
    alignas(64) json config;  // Align for cache-friendly access
    std::string configFilePath;
};