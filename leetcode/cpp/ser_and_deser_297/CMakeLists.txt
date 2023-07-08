set(TARGET ser_and_deser_297)
add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} PRIVATE fmt::fmt)
