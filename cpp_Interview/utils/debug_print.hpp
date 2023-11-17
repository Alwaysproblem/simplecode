#ifndef DEBUG_PRINT_HPP
#define DEBUG_PRINT_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
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

template <class _Tp, class _Container = std::deque<_Tp>>
void print(const std::stack<_Tp, _Container>& stack) {
  std::stack<_Tp, _Container> s(stack);
  std::cout << "[stack: ";
  while (!s.empty()) {
    fmt::print("{}| ", s.top());
    s.pop();
  }
  fmt::print("#]\n");
}

template <class _Tp, class _Container = std::deque<_Tp>>
void print(const std::queue<_Tp, _Container>& queue) {
  std::queue<_Tp, _Container> q(queue);
  std::cout << "[queue: ";
  while (!q.empty()) {
    fmt::print("{}| ", q.front());
    q.pop();
  }
  fmt::print("#]\n");
}

template <typename _Tp, typename _Container = std::vector < _Tp >, typename _Compare = std::less < typename _Container :: value_type >>
void print(const std::priority_queue<_Tp, _Container, _Compare>& priority_queue) {
  std::priority_queue<_Tp, _Container, _Compare> pq(priority_queue);
  std::cout << "[priority_queue: ";
  while (!pq.empty()) {
    fmt::print("{}| ", pq.top());
    pq.pop();
  }
  fmt::print("#]\n");
}

#endif
