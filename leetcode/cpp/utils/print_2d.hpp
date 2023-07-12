#ifndef PRINT_2D_HPP
#define PRINT_2D_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
int max_length_of(const std::vector<std::vector<T>>& v) {
  int max_length = 0;
  for (const auto& vec : v) {
    for (const T x : vec) {
      max_length = max_length > fmt::format("{}", x).size()
                       ? max_length
                       : fmt::format("{}", x).size();
    }
  }
  return max_length;
}

template <typename T>
void print2D(const std::vector<std::vector<T>>& v) {
  int space_len = max_length_of(v);
  std::string format_str = "{} ";
  if (space_len) format_str = fmt::format("{{:>{}}}  ", space_len);

  for (const auto& col : v) {
    for (const T& row : col) {
      fmt::print(format_str, row);
    }
    fmt::print("\n");
  }
  fmt::print("\n");
}

#endif
