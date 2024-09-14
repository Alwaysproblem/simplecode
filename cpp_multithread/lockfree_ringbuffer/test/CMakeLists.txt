cmake_minimum_required(VERSION 3.2)
project(divider_tests)

add_subdirectory(lib/googletest)

include_directories(${DIVISION_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/divider_tests.cpp)

add_executable(divider_tests ${SOURCE_FILES})
target_link_libraries(divider_tests division gtest)
install(TARGETS divider_tests DESTINATION bin)

add_test(NAME divider_tests COMMAND divider_tests)

# add python test

# find_package( Python COMPONENTS Interpreter REQUIRED)

# add_test( NAME add_index_test COMMAND ${Python_EXECUTABLE}
# ${CMAKE_CURRENT_SOURCE_DIR}/add_index_test.py WORKING_DIRECTORY
# ${CMAKE_SOURCE_DIR}/build/src)

# add_test( NAME add_index_float_test COMMAND ${Python_EXECUTABLE}
# ${CMAKE_CURRENT_SOURCE_DIR}/add_index_float_test.py WORKING_DIRECTORY
# ${CMAKE_SOURCE_DIR}/build/src)
