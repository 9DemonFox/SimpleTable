project(SimpleTable VERSION 1.0.0)
add_definitions(-std=c++11 -lpthread)

SET(BOOST_ROOT ../boost/) 
find_package(Boost REQUIRED)

if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()
add_executable(main main.cpp)
target_link_libraries(main PRIVATE simpletable)