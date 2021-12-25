include_directories(include)
add_library(httpclient SHARED client.cpp messages/request.cpp)
target_compile_options(httpclient PUBLIC -O2 -Wall -pedantic -Wextra)
target_link_libraries(httpclient pthread)