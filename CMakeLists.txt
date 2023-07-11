cmake_minimum_required(VERSION 3.25)
project(tcpIp)

set(CMAKE_CXX_STANDARD 17)

add_executable(tcpIp main.cpp hello_client.cpp echo_server.cpp echo_client.cpp)
