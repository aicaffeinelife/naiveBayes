cmake_minimum_required(VERSION 3.13.1)
project(nb)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "-g")

include_directories(include)
add_executable(nb
  src/nb.cc
  src/data_utils.cc
  src/main.cc
 )
