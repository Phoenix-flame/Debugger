cmake_minimum_required(VERSION 3.6)
project(Debugger)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread ")
# Add sub directories
add_subdirectory(phoenix)
add_subdirectory(Debugger)


file(COPY assets DESTINATION Debugger)