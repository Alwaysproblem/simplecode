set(TARGET ExamRoom)
add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} PRIVATE fmt::fmt Threads::Threads)
