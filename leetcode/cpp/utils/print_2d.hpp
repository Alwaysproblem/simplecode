#ifndef PRINT_2D_HPP
#define PRINT_2D_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <string>
#include <vector>

template <typename T>
void print2D(const std::vector<std::vector<T>>& v) {
  for (const auto& col: v){
    for (const T& row: col){
      fmt::print("{} ", row);
    }
    fmt::print("\n");
  }
  fmt::print("\n");
}

#endif
