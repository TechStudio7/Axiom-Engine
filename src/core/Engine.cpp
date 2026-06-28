#include "axiom/Engine.hpp"

#include "axiom/Logger.hpp"
#include "axiom/Scripting.hpp"
#include "axiom/Time.hpp"

#include <iostream>

namespace axiom {

void axiom_platform_info() {
    std::cout << "Platform support ready" << std::endl;
}

Engine::Engine() : name_("Axiom Engine") {
    Logger::instance().info("Engine initialized");
    Scripting::initializeJava();
    Scripting::initializeLua();
}

std::string Engine::title() const {
    return name_;
}

void Engine::run() {
    Logger::instance().info("Welcome to " + title());
    addScene(Scene("MainScene"));

    for (int i = 0; i < 3; ++i) {
        Time::tick();
        Logger::instance().info("Frame " + std::to_string(i + 1) + " dt=" + std::to_string(Time::deltaTime()));
    }

    Logger::instance().info(Scripting::runLuaScript("print('hello')"));
    Logger::instance().info(Scripting::runJavaSnippet("System.out.println('hello');"));
}

void Engine::addScene(Scene scene) {
    scenes_.push_back(std::move(scene));
    Logger::instance().info("Loaded scene: " + scenes_.back().name());
}

}  // namespace axiom
