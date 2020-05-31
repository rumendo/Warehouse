cmake_minimum_required(VERSION 3.14)
project(Warehouse)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
set(CMAKE_CXX_COMPILER /usr/bin/g++)

add_executable(Warehouse main.cpp Product.cpp Product.h Date.cpp Date.h Warehouse.cpp Warehouse.h Storage.cpp Storage.h)