cmake_minimum_required(VERSION 3.20)

project(
    PASS_Simulink_Backend
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# nlohmann/json
FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)

# cpp-httplib (single-header HTTP server)
FetchContent_Declare(
    httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG        v0.18.1
)
FetchContent_MakeAvailable(httplib)

include_directories(include)

set(SOURCES
    src/main.cpp

    src/Block/BlockManager.cpp
    src/Block/BlockFactory.cpp
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
    src/Graph/ProjectSerializer.cpp

    src/Engine/SignalRouter.cpp
    src/Engine/GraphExecutionEngine.cpp
    src/Engine/SimulationScheduler.cpp
)

add_executable(
    PASS_Simulink_Backend
    ${SOURCES}
)

target_link_libraries(
    PASS_Simulink_Backend
    PRIVATE
    nlohmann_json::nlohmann_json
    httplib::httplib
)

if(WIN32)
    target_link_libraries(PASS_Simulink_Backend PRIVATE ws2_32)
endif()

if(MSVC)
    target_compile_options(
        PASS_Simulink_Backend
        PRIVATE
        /W4
        /wd4702
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