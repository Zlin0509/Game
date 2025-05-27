cmake_minimum_required(VERSION 3.31)
project(Game LANGUAGES CXX)

# 设定 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 可执行文件输出到 bin 目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 下载 SFML 3.0.1
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        SYSTEM)
FetchContent_MakeAvailable(SFML)

# 可执行程序
add_executable(Game
        src/main.cpp
        #        src/Player.cpp
)

# 链接 SFML 模块
target_link_libraries(Game
        PRIVATE SFML::Graphics
)
