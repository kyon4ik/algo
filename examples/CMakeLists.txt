add_executable(numth numth.cpp)
target_link_libraries(numth PRIVATE asan ubsan algo)
target_include_directories(numth PRIVATE ../include)

add_executable(sequence sequence.cpp)
target_link_libraries(sequence PRIVATE asan ubsan algo)
target_include_directories(sequence PRIVATE ../include)

add_executable(sort sort.cpp)
target_link_libraries(sort PRIVATE asan ubsan algo)
target_include_directories(sort PRIVATE ../include)

add_executable(trie trie.cpp)
target_link_libraries(trie PRIVATE asan ubsan algo)
target_include_directories(trie PRIVATE ../include)

add_executable(io io.cpp)
target_link_libraries(io PRIVATE asan ubsan algo)
target_include_directories(io PRIVATE ../include)
