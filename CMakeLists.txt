cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

INCLUDE(FindPkgConfig)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS}  ${SDL2_TTF_INCLUDE_DIRS} src)

add_executable(SpaceInvaders src/main.cpp src/renderer.cpp src/controller.cpp src/game.cpp src/rectangle.cpp src/player.cpp src/projectile.cpp src/enemy.cpp src/button.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SpaceInvaders ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
