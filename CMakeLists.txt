cmake_minimum_required(VERSION 3.16)
project(TowerDefense)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR /usr/local/SFML/lib/cmake/SFML)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(TowerDefense src/main.cpp)
target_link_libraries(TowerDefense sfml-graphics sfml-window sfml-system)
