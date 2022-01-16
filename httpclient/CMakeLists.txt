include_directories(include)
set(src src/httpclient.cpp src/request.cpp src/response.cpp)
add_library(httpclient SHARED ${src})
target_compile_options(httpclient PRIVATE -O2 -Wall -Weffc++ -pedantic -Wextra)
target_link_libraries(httpclient pthread)

if(${COMPILE_TESTS})
	add_subdirectory(tests)
endif()
