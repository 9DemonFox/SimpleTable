project(SimpleTable VERSION 1.0.0)
add_definitions(-std=c++11 -lpthread)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE libtable)