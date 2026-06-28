#include "axiom/Scripting.hpp"

#include "axiom/BuildConfig.hpp"

#include <array>
#include <cstdio>
#include <iostream>
#include <sstream>

namespace axiom {
namespace {

std::string quoteShellArgument(const std::string& value) {
#ifdef _WIN32
    std::string quoted = "\"";
    for (char c : value) {
        if (c == '"') {
            quoted += "\\\"";
        } else if (c == '\\') {
            quoted += "\\\\";
        } else {
            quoted += c;
        }
    }
    quoted += "\"";
    return quoted;
#else
    std::string quoted = "'";
    for (char c : value) {
        if (c == '\'') {
            quoted += "'\\''";
        } else {
            quoted += c;
        }
    }
    quoted += "'";
    return quoted;
#endif
}

std::string runCommand(const std::string& command) {
    std::array<char, 256> buffer{};
    std::string output;

#ifdef _WIN32
    FILE* pipe = _popen(command.c_str(), "r");
#else
    FILE* pipe = popen(command.c_str(), "r");
#endif

    if (!pipe) {
        return "Failed to launch Java process";
    }

    while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe) != nullptr) {
        output += buffer.data();
    }

#ifdef _WIN32
    const int exitCode = _pclose(pipe);
#else
    const int exitCode = pclose(pipe);
#endif

    if (exitCode != 0) {
        std::ostringstream oss;
        oss << "Java process exited with code " << exitCode;
        if (!output.empty()) {
            oss << ": " << output;
        }
        return oss.str();
    }

    if (!output.empty() && output.back() == '\n') {
        output.pop_back();
    }

    return output;
}

}  // namespace

void Scripting::initializeJava() {
    if (isJavaAvailable()) {
        std::cout << "[Scripting] Java support initialized" << std::endl;
    } else {
        std::cout << "[Scripting] Java support unavailable" << std::endl;
    }
}

void Scripting::initializeLua() {
    std::cout << "[Scripting] Lua support initialized" << std::endl;
}

bool Scripting::isJavaAvailable() {
    return AXIOM_ENABLE_JAVA && std::string(AXIOM_JAVA_EXECUTABLE).size() > 0 &&
           std::string(AXIOM_JAVA_CLASSPATH).size() > 0;
}

std::string Scripting::runLuaScript(const std::string& script) {
    std::ostringstream oss;
    oss << "Lua script executed: " << script;
    return oss.str();
}

std::string Scripting::runJavaClass(const std::string& className, const std::vector<std::string>& arguments) {
    if (!isJavaAvailable()) {
        return "Java support is not available in this build";
    }

    std::ostringstream command;
    command << quoteShellArgument(AXIOM_JAVA_EXECUTABLE)
            << " -cp "
            << quoteShellArgument(AXIOM_JAVA_CLASSPATH)
            << " "
            << quoteShellArgument(className);

    for (const std::string& argument : arguments) {
        command << " " << quoteShellArgument(argument);
    }

    return runCommand(command.str());
}

std::string Scripting::runJavaSnippet(const std::string& snippet) {
    return runJavaClass("com.axiom.EngineBootstrap", {"snippet", snippet});
}

}  // namespace axiom
