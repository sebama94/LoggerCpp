#include "loggerCpp/networkLogSink.hpp"

void NetworkLogSink::write(const utils::LogEvent& event) {
    // TODO: Implement network logging
    // This would send logs to a remote logging service
    std::cerr << "Error: Network logging not implemented\n";
    throw std::runtime_error("Network logging not implemented");
}
