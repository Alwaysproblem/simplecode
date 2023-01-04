#include <iostream>
#include <unordered_map>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace std;

int main()
{
  unordered_map<int, int> v{{1, 3}, {2, 4}, {3, 5}};
  fmt::print("{}\n", v.count(1));
  return 0;
}
