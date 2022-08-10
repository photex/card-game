cmake_minimum_required(VERSION 3.22)

project(card-game CXX)

set(CMAKE_CXX_STANDARD 20)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

add_library(cardgame src/lib.cpp)
target_include_directories(cardgame
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(cardgame-bin test/main.cpp)
target_link_libraries(cardgame-bin cardgame)

add_executable(best-of test/bestof.cpp)
target_link_libraries(best-of cardgame)
