set(ALGO_SRC 
    numth.cpp)

add_library(algo STATIC ${ALGO_SRC})
target_include_directories(algo PUBLIC ../include)
