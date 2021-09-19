cmake_minimum_required(VERSION 3.20)
project(TinyHttp)

set(CMAKE_CXX_STANDARD 11)

include_directories(log threadpool queue)
file(GLOB SOURCES log/*.cpp)
add_executable(server main.cpp ${SOURCES})

target_link_libraries(server -lpthread)
