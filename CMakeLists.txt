project(Coke8080)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++17")
file(GLOB_RECURSE Source src/*.cpp)

include_directories("include/")

add_executable(Coke8080 ${Source})

set(SFML_DIR "./cmake_modules/SFML")

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(Coke8080 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
