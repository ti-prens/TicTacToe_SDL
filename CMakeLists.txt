cmake_minimum_required(VERSION 3.0)
project(tictactoe)

# set(SDL2_INCLUDE_DIR "C:/Program Files (x86)/SDL2/include")
# set(SDL2_LIBRARY_DIR "C:/Program Files (x86)/SDL2/lib")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

add_executable(ttt tictactoe.c)
target_link_libraries(ttt ${SDL2_LIBRARY})
