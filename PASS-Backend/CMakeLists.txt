cmake_minimum_required(VERSION 3.20)

project(
    PASS_Simulink_Backend
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

set(SOURCES
    src/main.cpp

    src/Block/BlockManager.cpp
    src/Block/ClockBlock.cpp
    src/Block/SineBlock.cpp
    src/Block/CosineBlock.cpp
    src/Block/ScopeBlock.cpp
    src/Block/AddBlock.cpp
    src/Block/MultiplyBlock.cpp
    src/Block/AverageBlock.cpp
    src/Block/GainBlock.cpp
    src/Block/SubtractBlock.cpp
    src/Block/MinBlock.cpp
    src/Block/MaxBlock.cpp

    src/Graph/ConnectionManager.cpp
    src/Graph/TopologicalSorter.cpp

    src/Engine/SignalRouter.cpp
    src/Engine/GraphExecutionEngine.cpp
)

add_executable(
    PASS_Simulink_Backend
    ${SOURCES}
)

if(MSVC)
    target_compile_options(
        PASS_Simulink_Backend
        PRIVATE
        /W4
    )

else()
    target_compile_options(
        PASS_Simulink_Backend
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )

endif()