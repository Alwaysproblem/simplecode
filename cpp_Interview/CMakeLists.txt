cmake_minimum_required(VERSION 3.10.0)
project(simplecode VERSION 0.1.0)

find_package(fmt CONFIG REQUIRED)

# set(CMAKE_CXX_STANDARD c++17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(LL)
add_subdirectory(BinaryTree)
