cmake_minimum_required(VERSION 3.6)
project(rgb_clustering)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost)
find_package(Jpeg)
#set(Boost_USE_MULTITHREADED ON)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES main.cpp Element.cpp Element.h Lattice.h Cluster.cpp Cluster.h Limits.cpp Limits.h Processor.cpp Processor.h)
add_executable(rgb_clustering ${SOURCE_FILES})
target_link_libraries(rgb_clustering ${JPEG_LIBRARIES})