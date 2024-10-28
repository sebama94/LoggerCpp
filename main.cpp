#include "configurationManager.hpp"
#include <csignal>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>
#include <stdexcept>

namespace {
    // Global ConfigurationManager instance
    std::unique_ptr<ConfigurationManager> g_configManager;

    // Signal handler function
    void signalHandler(int signum) {
        const char* signal_name = nullptr;
        switch (signum) {
            case SIGTERM:
                signal_name = "SIGTERM";
                break;
            case SIGINT: 
                signal_name = "SIGINT";
                break;
            default:
                LOG_ERROR("Received unknown signal " + std::to_string(signum) + ". Exiting...");
                g_configManager.reset();
                std::exit(signum);
        }
        
        LOG_INFO("Received " + std::string(signal_name) + " signal. Performing cleanup...");
        g_configManager.reset();
        std::exit(signum);
    }
}

int main() {
    try {
        // Register signal handlers using std::signal for better type safety
        std::signal(SIGTERM, signalHandler);
        std::signal(SIGINT, signalHandler);
        
        const std::filesystem::path config_path = std::filesystem::current_path() / "config.json";
        
        // Verify config file exists before attempting to load
        if (!std::filesystem::exists(config_path)) {
            throw std::runtime_error("Configuration file not found: " + config_path.string());
        }
        
        // Initialize ConfigurationManager with the path to the JSON config file
        g_configManager = std::make_unique<ConfigurationManager>(config_path.string());
        
        // Sample log messages demonstrating all log levels
        LOG_DEBUG("Initializing application...");
        LOG_INFO("Application started successfully");
        

        LOG_WARN("Processing time exceeded 10 seconds");
        LOG_ERROR("Failed to complete all tasks in time");
        LOG_CRITICAL("System resources critically low");
        
        // Clean up before exiting
        g_configManager.reset();
        
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        LOG_CRITICAL("Fatal error: " + std::string(e.what()));
        return EXIT_FAILURE;
    }
}
