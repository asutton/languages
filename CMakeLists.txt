
cmake_minimum_required(VERSION 3.15)

project(lang)

set(CMAKE_CXX_FLAGS "-std=c++2a -fsanitize=address -fsanitize=leak -fsanitize=undefined")

add_subdirectory(src)
