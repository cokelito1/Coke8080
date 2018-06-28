project(Coke8080)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++14")
file(GLOB_RECURSE Source src/*.cpp)

include_directories("include/")

add_executable(Coke8080 ${Source})

set(SFML_DIR "./cmake_modules/SFML")
