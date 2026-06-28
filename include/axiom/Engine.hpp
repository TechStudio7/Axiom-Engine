#pragma once

#include <string>
#include <vector>

#include "axiom/Scene.hpp"

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
