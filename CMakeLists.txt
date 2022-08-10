cmake_minimum_required(VERSION 3.22)

project(card-game CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(cardgame src/lib.cpp)
target_include_directories(cardgame
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(cardgame-bin test/main.cpp)
target_link_libraries(cardgame-bin cardgame)
