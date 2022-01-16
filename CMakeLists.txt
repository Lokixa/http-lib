cmake_minimum_required(VERSION 3.22)
project(http-lib VERSION 0.0.1 LANGUAGES CXX)

include(cmake/CPM.cmake)
cpmaddpackage("gh:TheLartians/Format.cmake@1.7.3")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_CXX_STANDARD 17)
set(COMPILE_TESTS TRUE)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

if(${COMPILE_TESTS})
    enable_testing() 
    include(GoogleTest)
endif()

add_subdirectory(httpclient)

add_subdirectory(tls)
