project(Test VERSION 1.0.0)
add_definitions(-std=c++11)

add_executable(test test.cpp)
target_link_libraries(test PRIVATE libtable)