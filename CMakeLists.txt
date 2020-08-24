cmake_minimum_required(VERSION 3.0)

project(custom_socket)

add_executable(server src/server.cpp src/connection.h)
add_executable(client src/client.cpp src/connection.h)

