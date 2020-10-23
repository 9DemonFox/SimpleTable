project(Test VERSION 1.0.0)
add_definitions(-std=c++11)

add_executable(test testmain.cpp test.cpp) # 将catch分离，加快编译
target_link_libraries(test PRIVATE libtable pthread)