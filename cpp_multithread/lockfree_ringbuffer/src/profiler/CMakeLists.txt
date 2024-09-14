cmake_minimum_required(VERSION 3.2)
project(profiler C CXX)

set(SOURCE_FILES profiler.h profiler.cpp)

add_library(profiler SHARED STATIC ${SOURCE_FILES})

install(TARGETS profiler DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
install(FILES profiler.h DESTINATION ${DIVISIBLE_INSTALL_INCLUDE_DIR})
