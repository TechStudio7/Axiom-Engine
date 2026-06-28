#pragma once

#include <string>

namespace axiom {

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    static Logger& instance();

    void setLogLevel(LogLevel level);
    void info(const std::string& message);
    void warn(const std::string& message);
    void error(const std::string& message);

private:
    LogLevel level_ = LogLevel::Info;
};

}  // namespace axiom
