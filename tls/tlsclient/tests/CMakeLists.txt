add_executable(tlsclient_test tests_main.cpp tlsclient_test.cpp)
target_link_libraries(tlsclient_test tlsclient gtest)
gtest_discover_tests(tlsclient_test)
