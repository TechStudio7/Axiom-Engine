#pragma once

#include <string>

namespace axiom {

class Scene {
public:
    explicit Scene(std::string name);
    const std::string& name() const;
    void update();

private:
    std::string name_;
};

}  // namespace axiom
