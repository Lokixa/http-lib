include_directories(include)
add_library(httpclient SHARED client.cpp messages/request.cpp)
target_compile_options(httpclient PUBLIC ${compile_options})
target_link_libraries(httpclient pthread)