#include "axiom/Logger.hpp"

#include <iostream>

namespace axiom {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::setLogLevel(LogLevel level) {
    level_ = level;
}

void Logger::info(const std::string& message) {
    if (level_ <= LogLevel::Info) {
        std::cout << "[INFO] " << message << std::endl;
    }
}

void Logger::warn(const std::string& message) {
    if (level_ <= LogLevel::Warning) {
        std::cout << "[WARN] " << message << std::endl;
    }
}

void Logger::error(const std::string& message) {
    if (level_ <= LogLevel::Error) {
        std::cout << "[ERROR] " << message << std::endl;
    }
}

}  // namespace axiom
