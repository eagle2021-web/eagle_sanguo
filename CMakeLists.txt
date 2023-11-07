cmake_minimum_required(VERSION 3.20)
project(sanguo)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp)
add_executable(untitled2 abc.cpp)
add_executable(zhaobing zhaobing.cpp)
add_executable(chehuizhujun chehuizhujun.cpp)
add_executable(endian endian.cpp)
add_executable(win_client win_client.cpp)
add_executable(tmp tmp.cpp)
add_executable(xiangsu xiangsu.cpp)

add_definitions(-DUNICODE -D_UNICODE)

target_link_libraries(win_client wsock32)
