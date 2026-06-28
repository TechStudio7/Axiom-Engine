cmake_minimum_required(VERSION 3.16)
project(AxiomEngine VERSION 0.1.0 LANGUAGES CXX)

include(CheckLanguage)

check_language(OBJCXX)
if(CMAKE_OBJCXX_COMPILER)
    enable_language(OBJCXX)
    message(STATUS "Objective-C++ support enabled")
    set(AXIOM_ENABLE_OBJCXX ON)
else()
    message(STATUS "Objective-C++ compiler not available; Objective-C++ sources will be skipped")
    set(AXIOM_ENABLE_OBJCXX OFF)
endif()

check_language(Java)
if(CMAKE_Java_COMPILER)
    enable_language(Java)
    include(UseJava)
    find_package(Java COMPONENTS Runtime Development)
endif()

if(Java_FOUND AND Java_JAVA_EXECUTABLE AND Java_JAVAC_EXECUTABLE)
    set(AXIOM_ENABLE_JAVA ON)
    set(AXIOM_JAVA_JAR ${CMAKE_CURRENT_BINARY_DIR}/axiom_java_classes.jar)
    message(STATUS "Java support enabled")
else()
    set(AXIOM_ENABLE_JAVA OFF)
    set(AXIOM_JAVA_JAR "")
    message(STATUS "Java toolchain not available; Java scripting support will be disabled")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/AxiomBuildConfig.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/axiom/BuildConfig.hpp
    @ONLY
)

set(AXIOM_ENGINE_SOURCES
    src/core/Engine.cpp
    src/core/Logger.cpp
    src/core/Time.cpp
    src/core/Scene.cpp
    src/scripting/Scripting.cpp
)

if(AXIOM_ENABLE_OBJCXX)
    list(APPEND AXIOM_ENGINE_SOURCES src/platform/Platform.mm)
endif()

add_library(axiom_engine STATIC ${AXIOM_ENGINE_SOURCES})

target_include_directories(axiom_engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/generated
)

if(AXIOM_ENABLE_JAVA)
    add_jar(axiom_java_classes
        SOURCES
            src/java/com/axiom/EngineBootstrap.java
        OUTPUT_NAME axiom_java_classes
        ENTRY_POINT com.axiom.EngineBootstrap
    )

    target_compile_definitions(axiom_engine PRIVATE AXIOM_HAS_JAVA=1)
else()
    target_compile_definitions(axiom_engine PRIVATE AXIOM_HAS_JAVA=0)
endif()

add_executable(axiom_app
    src/main.cpp
)

target_link_libraries(axiom_app PRIVATE axiom_engine)
if(AXIOM_ENABLE_JAVA)
    add_dependencies(axiom_engine axiom_java_classes)
    add_dependencies(axiom_app axiom_java_classes)
endif()
