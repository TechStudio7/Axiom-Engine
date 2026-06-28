#pragma once

#include <string>
#include <vector>

namespace axiom {

class Scripting {
public:
    static void initializeJava();
    static void initializeLua();
    static bool isJavaAvailable();
    static std::string runLuaScript(const std::string& script);
    static std::string runJavaClass(const std::string& className, const std::vector<std::string>& arguments = {});
    static std::string runJavaSnippet(const std::string& snippet);
};

}  // namespace axiom
