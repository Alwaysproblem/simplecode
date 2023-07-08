#ifndef DEBUG_RECURSIVE_HPP
#define DEBUG_RECURSIVE_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>

template <typename... T>
void debug_recursive(std::string format, int level, T&&... args) {
  std::string indent = "    ";
  for (int i = 0; i <= level; i++) {
    fmt::print("{}", indent);
  }
  fmt::print(format, args...);
}

#endif
