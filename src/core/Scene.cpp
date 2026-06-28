#include "axiom/Scene.hpp"

namespace axiom {

Scene::Scene(std::string name) : name_(std::move(name)) {}

const std::string& Scene::name() const {
    return name_;
}

void Scene::update() {
}

}  // namespace axiom
