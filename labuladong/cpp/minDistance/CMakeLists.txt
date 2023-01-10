set(TARGET minDistance)
add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} PRIVATE fmt::fmt)
