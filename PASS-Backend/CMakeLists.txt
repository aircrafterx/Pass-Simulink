cmake_minimum_required(VERSION 3.20)

project(PASS_Simulink_Backend)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PASS_Simulink_Backend
    src/main.cpp
    src/Clock/ClockBlock.cpp
    src/Sine/SineBlock.cpp
    src/Cosine/CosineBlock.cpp
    src/Scope/ScopeBlock.cpp
    src/Engine/ExecutionEngine.cpp
    src/Graph/ConnectionManager.cpp
)

target_include_directories(PASS_Simulink_Backend
    PRIVATE
        include
)