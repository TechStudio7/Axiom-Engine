# Axiom Engine

A minimal CMake-based starter project for the Axiom Engine framework.

This project is open source and licensed under the MIT License.

## Build

```bash
cmake -S . -B build
cmake --build build
```

Java scripting support is enabled automatically when CMake can find a full JDK
with both `java` and `javac`. If only a Java runtime is available, Axiom still
builds and reports Java scripting as unavailable at runtime.

## Run

```bash
./build/axiom_app
```
