#pragma once

#include <chrono>

namespace axiom {

class Time {
public:
    static float deltaTime();
    static float elapsedTime();
    static void tick();

private:
    static std::chrono::steady_clock::time_point start_;
    static std::chrono::steady_clock::time_point last_;
    static float delta_time_;
    static float elapsed_time_;
};

}  // namespace axiom
