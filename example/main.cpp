#include "loggerCpp/configurationManager.hpp"
#include <csignal>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>
#include <stdexcept>


namespace {
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
                LOG_ERROR("Received unknown signal {}", signum);
                std::exit(signum);
        }
        
        LOG_INFO("Received {} signal. Performing cleanup...", signal_name);
        std::exit(signum);
    }
}

int main() {
   //std::unique_ptr<ConfigurationManager> g_configManager;
    try {
        // Register signal handlers using std::signal for better type safety
        std::signal(SIGTERM, signalHandler);
        std::signal(SIGINT, signalHandler);
        
        // Initialize ConfigurationManager with the path to the JSON config file
        ConfigurationManager configManager(utils::LogLevel::DEBUG); 
       // g_configManager = std::make_unique<ConfigurationManager>(utils::LogLevel::DEBUG);

        configManager.applyConsoleSink(utils::LogLevel::DEBUG);
        configManager.applyFileSink(utils::LogLevel::INFO, "log.log");
        
        // Sample log messages demonstrating all log levels
        LOG_DEBUG("Initializing application...");
        LOG_INFO("Application started successfully");
        // Add a small delay to simulate processing
        std::this_thread::sleep_for(std::chrono::seconds(5));
        int a = 10;
        LOG_WARN("Processing time exceeded 10 seconds: {}", a);
        std::vector<int> vec = {1, 2, 3, 4, 5};
        LOG_ERROR("Failed to complete all tasks in time: {}", fmt::join(vec.begin(), vec.end(), ", "));
        LOG_CRITICAL("System resources critically low");

        // Clean up before exiting
    
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
       // g_configManager.reset();
        return EXIT_FAILURE;
    }
}
