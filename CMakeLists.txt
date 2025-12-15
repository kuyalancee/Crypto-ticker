cmake_minimum_required(VERSION 3.14)
project(CryptoTicker)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(USE_TLS ON)
set(USE_OPEN_SSL ON)

FetchContent_Declare(
    ixwebsocket
    GIT_REPOSITORY https://github.com/machinezone/IXWebSocket.git
    GIT_TAG v11.4.6
)
FetchContent_MakeAvailable(ixwebsocket)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

add_executable(ticker main.cpp)

target_link_libraries(ticker PRIVATE ixwebsocket nlohmann_json::nlohmann_json)

if(UNIX)
    target_link_libraries(ticker PRIVATE pthread ssl crypto z)
endif()