cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR /usr/local/SFML/lib/cmake/SFML)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(TowerDefense
    src/main.cpp
    src/Game.hpp src/Game.cpp
    src/Enemy.hpp src/Enemy.cpp
    src/Tower.hpp src/Tower.cpp
    src/Tile.hpp src/Config.hpp
)
target_link_libraries(TowerDefense sfml-graphics sfml-window sfml-system)