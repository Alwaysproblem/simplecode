/*
 * @lc app=leetcode.cn id=990 lang=cpp
 *
 * [990] 等式方程的可满足性
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class UnionFind {
 public:
  UnionFind() = delete;
  UnionFind(int n) : count(n) {
    parent.reserve(n);
    for (int i = 0; i < n; i++) {
      parent.emplace_back(i);
    }
  }

  void Union(int p, int q) {
    int rootP = find(p);
    int rootQ = find(q);

    if (rootP == rootQ) return;
    parent[rootQ] = rootP;
    count--;
  }

  bool connected(int p, int q) { return find(p) == find(q); }

  int find(int x) {
    if (parent[x] != x) {
      parent[x] = find(parent[x]);
    }
    return parent[x];
  }

  int get_count() const { return count; }

 private:
  int count;
  vector<int> parent;
};

class Solution {
 public:
  bool equationsPossible(vector<string>& equations) {
    UnionFind uf(26);
    char lhs = 0, rhs = 0;
    for (string &e : equations){
      lhs = e.at(0);
      rhs = e.at(3);
      if (e.at(1) == '=')
        uf.Union(lhs - 'a', rhs - 'a');
    }

    for (string &e : equations){
      lhs = e.at(0);
      rhs = e.at(3);
      if (e.at(1) == '!')
        if (uf.connected(lhs - 'a', rhs - 'a'))
          return false;
    }

    return true;
  }
};
// @lc code=end

int main() {
  vector<string> equations = {"a==b", "b!=a"};
  Solution sol;
  bool v = sol.equationsPossible(equations);
  fmt::print("{}\n", v);
  return 0;
}
