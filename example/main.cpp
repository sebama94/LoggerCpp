#include "loggerCpp/configurationManager.hpp"
#include <csignal>
#include <memory>
#include <chrono>
#include <thread>
#include <filesystem>
#include <stdexcept>


const std::string log_file_path = std::filesystem::current_path().string() + "/log.log";

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
    try {
        std::signal(SIGTERM, signalHandler);
        std::signal(SIGINT, signalHandler);
        
        
        ConfigurationManager configManager; 


        configManager.applyFileSink(utils::LogLevel::INFO, log_file_path);
        configManager.applyConsoleSink(utils::LogLevel::ERROR);
        configManager.applySysLogSink(utils::LogLevel::ERROR, "loggerCppAPP");
        //
        LOG_DEBUG("Initializing application...");
        LOG_INFO("Application started successfully");
        LOG_ERROR("This is an error message");

        int a = 10;
        LOG_WARNING("Processing time exceeded 10 seconds: {}", a);
        std::vector<int> vec = {1, 2, 3, 4, 5};
        std::this_thread::sleep_for(std::chrono::seconds(10));
        //LOG_ERROR("Failed to complete all tasks in time: {}", fmt::join(vec.begin(), vec.end(), ", "));
        LOG_CRITICAL("System resources critically low");

        // Clean up before exiting
    
        return EXIT_SUCCESS;
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}
