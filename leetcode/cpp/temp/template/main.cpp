#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
  unordered_map<int, int> v{{1, 3}, {2, 4}, {3, NULL}};
  fmt::print("{}\n", v);
  return 0;
}
