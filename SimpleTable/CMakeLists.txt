project(simpletable)
add_definitions(-std=c++11)


SET(BOOST_ROOT ../boost/) 
find_package(Boost REQUIRED)

if(NOT Boost_FOUND)
    message("NOT found Boost")
endif()

aux_source_directory(src/ SRCS)
add_library(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include )
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
