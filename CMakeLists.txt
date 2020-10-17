cmake_minimum_required(VERSION 3.5.1)
project(SimpleTable VERSION 1.0.0)
add_definitions(-std=c++11)
include_directories(SimpleTable)
aux_source_directory(SimpleTable SOURCES)
add_library(
	libtable
	${SOURCES}
)

add_subdirectory(main)
add_subdirectory(test)