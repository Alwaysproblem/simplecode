cmake_minimum_required(VERSION 3.2)
project(temproject)

add_subdirectory(profiler)
set(SOURCE_FILES main.cpp)

add_executable(temproject ${SOURCE_FILES})
target_link_libraries(temproject profiler)
install(TARGETS temproject DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
