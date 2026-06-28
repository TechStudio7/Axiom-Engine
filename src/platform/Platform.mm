#include <iostream>

namespace axiom {

void printPlatformInfo() {
#if defined(__APPLE__)
    std::cout << "Platform: Apple Objective-C++ runtime" << std::endl;
#elif defined(_WIN32)
    std::cout << "Platform: Windows Objective-C++ runtime" << std::endl;
#else
    std::cout << "Platform: Generic Objective-C++ runtime" << std::endl;
#endif
}

}  // namespace axiom
