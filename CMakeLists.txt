cmake_minimum_required(VERSION 3.14...3.28)

project(algo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

set(CMAKE_CXX_STANDARD 20)
add_compile_options("$<$<CONFIG:DEBUG>:-Og>")
add_compile_options("$<$<CONFIG:DEBUG>:-Wall>")
add_compile_options("$<$<CONFIG:DEBUG>:-Wextra>")
add_compile_options("$<$<CONFIG:DEBUG>:-Wshadow>")
add_compile_options("$<$<CONFIG:DEBUG>:-ggdb>")
add_compile_options("$<$<CONFIG:DEBUG>:-fsanitize=address,undefined>")

# Ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(src)
add_subdirectory(examples)
