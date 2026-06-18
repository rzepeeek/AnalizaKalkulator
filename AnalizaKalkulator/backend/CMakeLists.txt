cmake_minimum_required(VERSION 3.16)

project(AnalizaKalkulator)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(server main.cpp)

target_link_libraries(server ws2_32)