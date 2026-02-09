cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Note the CAPITAL letters for SFML 3
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(SnakeGame main.cpp)

# Use the Namespaced targets
target_link_libraries(SnakeGame SFML::Graphics SFML::Window SFML::System)
