add_executable(test test.cpp)
target_link_libraries(test PRIVATE asan)
target_include_directories(test PRIVATE ..)
