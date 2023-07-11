cmake_minimum_required(VERSION 3.25)
project(tcpIp)

set(CMAKE_CXX_STANDARD 17)

add_executable(tcpIp chapter04/main.cpp chapter04/hello_client.cpp chapter04/echo_server.cpp chapter04/echo_client.cpp)
