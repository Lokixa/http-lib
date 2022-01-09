include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/httpclient/include)

set(src src/tlsclient.cpp)
set(compile_options -O2 -Wall -Weffc++ -pedantic -Wextra)
add_library(tlsclient SHARED ${src})
target_compile_options(tlsclient PRIVATE ${compile_options})
target_link_libraries(tlsclient httpclient crypto ssl)

if(COMPILE_TESTS)
	add_subdirectory(tests)
endif()
