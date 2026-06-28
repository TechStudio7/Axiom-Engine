cmake_minimum_required(VERSION 3.16)
project(AxiomEngine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(axiom_engine STATIC
    src/core/Engine.cpp
    src/core/Logger.cpp
    src/core/Time.cpp
    src/core/Scene.cpp
)

target_include_directories(axiom_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(axiom_app
    src/main.cpp
)

target_link_libraries(axiom_app PRIVATE axiom_engine)
