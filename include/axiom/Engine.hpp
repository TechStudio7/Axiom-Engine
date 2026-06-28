#pragma once

#include <string>
#include <vector>

#include "axiom/Scene.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void axiom_platform_info();

#ifdef __cplusplus
}
#endif

namespace axiom {

class Engine {
public:
    Engine();
    std::string title() const;
    void run();
    void addScene(Scene scene);

private:
    std::string name_;
    std::vector<Scene> scenes_;
};

}  // namespace axiom
