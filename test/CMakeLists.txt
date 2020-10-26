project(Test VERSION 1.0.0)
add_definitions(-std=c++11)

find_package(Boost COMPONENTS serialization REQUIRED)

if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS})


add_executable(test testmain.cpp test.cpp) # 将catch分离，加快编译
target_link_libraries(test PRIVATE libtable pthread ${Boost_LIBRARIES})