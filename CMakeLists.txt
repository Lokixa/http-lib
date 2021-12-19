cmake_minimum_required(VERSION 3.20)
project(http-lib VERSION 0.0.1 LANGUAGES CXX)

set(CXX_STANDARD 11)

set(src main.cpp)
add_executable(main ${src})
target_compile_options(main PUBLIC -O2 -Wall -Weffc++ -pedantic -Wextra)
add_library(httpclient libs/httpclient/httpclient.cpp)
target_link_libraries(main pthread httpclient)