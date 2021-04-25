project(tests VERSION 1.0.0)
add_definitions(-std=c++11)


SET(BOOST_ROOT "../boost")
set(BOOST_INCLUDEDIR "../boost/include")
SET(BOOST_LIBRARYDIR "../boost/lib") 
find_package(Boost COMPONENTS serialization REQUIRED)
if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()

include_directories(${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/../SimpleTable/include)

add_executable(tests testmain.cpp test.cpp) # 将catch分离，加快编译

target_link_libraries(${PROJECT_NAME} PUBLIC simpletable pthread ${Boost_LIBRARIES})



