cmake_minimum_required(VERSION 3.14)

project(hello)

set(CMAKE_CXX_STANDARD 11)

add_executable(client client.cpp)
add_executable(server server.cpp)
add_executable(error thread/error.cpp)
add_executable(basic thread/basic.cpp)
add_executable(mutex thread/mutex.cpp)
add_executable(pools thread/threadpool.cpp)