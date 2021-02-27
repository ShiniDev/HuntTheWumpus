cmake_minimum_required(VERSION 3.5)
project(HuntTheWumpus)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++14 -ggdb -O3")

add_library(
    huntthewumpus
    src/Room.cpp
    src/GameMap.cpp
    src/Game.cpp
    src/headers/GameMap.hpp
    src/headers/Player.hpp
    src/headers/Room.hpp
    src/headers/Game.hpp
    )

add_executable(
    main
    main.cpp
    )
target_link_libraries(main PUBLIC huntthewumpus)
