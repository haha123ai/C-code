#指定cmake的最低版本
cmake_minimum_required(VERSION 3.14)

#指定工程名称
project(hello)

#指头文件定搜索路径
include_directories(./)

#自动把src目录下面的cpp文件添加到项目里
#file(GLOB_RECURSE SOURCES "practice_socket/*.cpp") #获取src目录下面的所有cpp文件，并将其保存在变量中

#file(GLOB_RECURSE SERVER_SOURCES "practice_socket/socket.cpp")
#file(GLOB_RECURSE CLIENT_SOURCES "practice_socket/socket.cpp")


#使用指定的源文件生成目标可执行文件。多文件编译就多写几个
#add_executable(server ${SERVER_SOURCES} practice_socket/ss.cpp)
#add_executable(client ${CLIENT_SOURCES} practice_socket/cc.cpp)

#add_executable(server ${SOURCES} server.cpp)

add_executable(server practice_socket/ss.cpp)
add_executable(client practice_socket/cc.cpp)

#使用C++ 新特性，比如C++11，C++14,C++17
set(CMAKE_CXX_STANDARD 11)

#给后续的目标加上编译选项,-Wunused为使用的变量加上警告
add_compile_options(-g -Wunused)

#给指定的目标加上编译选项,更强编译选项设置
#target_compile_options(server PUBLIC -Wall -Werror)

