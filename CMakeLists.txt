cmake_minimum_required(VERSION 3.20)
project(http-lib VERSION 0.0.1 LANGUAGES CXX)

set(CXX_STANDARD 11)

set(src main.cpp)
set(compile_options -O2 -Wall -Weffc++ -pedantic -Wextra)

include_directories(include)
set(include_dirs include)

add_subdirectory(client)
list(APPEND include_dirs client/include)

add_executable(main ${src})
target_compile_options(main PUBLIC ${compile_options})
target_include_directories(main PUBLIC ${include_dirs})

target_link_libraries(main httpclient)