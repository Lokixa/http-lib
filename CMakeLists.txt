cmake_minimum_required(VERSION 3.22)
project(http-lib VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(src main.cpp)
set(compile_options -O2 -Wall -Weffc++ -pedantic -Wextra)

include_directories(include)
set(include_dirs include)

add_subdirectory(client)
list(APPEND include_dirs client/include)

add_subdirectory(tlsclient)
list(APPEND include_dirs tlsclient/include)

add_executable(main ${src})
target_compile_options(main PUBLIC ${compile_options})
target_include_directories(main PUBLIC ${include_dirs})

target_link_libraries(main httpclient tlsclient)
