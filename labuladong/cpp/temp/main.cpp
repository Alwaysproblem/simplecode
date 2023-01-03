#include <iostream>
#include <map>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>

using namespace std;

int main()
{
  vector<int> v{1, 6, 3, 2, 5};
  fmt::print("{}\n", v);
  return 0;
}
