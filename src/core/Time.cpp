#include "axiom/Time.hpp"

namespace axiom {

std::chrono::steady_clock::time_point Time::start_ = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point Time::last_ = start_;
float Time::delta_time_ = 0.0f;
float Time::elapsed_time_ = 0.0f;

float Time::deltaTime() {
    return delta_time_;
}

float Time::elapsedTime() {
    return elapsed_time_;
}

void Time::tick() {
    const auto now = std::chrono::steady_clock::now();
    const auto elapsed = std::chrono::duration<float>(now - last_).count();
    last_ = now;
    delta_time_ = elapsed;
    elapsed_time_ = std::chrono::duration<float>(now - start_).count();
}

}  // namespace axiom
