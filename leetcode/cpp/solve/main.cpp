/*
 * @lc app=leetcode.cn id=130 lang=cpp
 *
 * [130] 被围绕的区域
 * title: surrounded-regions
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

#include "utils/debug_print.hpp"

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
  int get_index(int row, int col, int m) { return col * m + row; }

  void solve(vector<vector<char>>& board) {
    int n = board.size();
    int m = board[0].size();
    UnionFind uf{n * m + 1};
    int dummy = m * n;
    for (int col = 0; col < n; col++) {
      if (board[col][0] == 'O') uf.Union(dummy, col * m + 0);
      if (board[col][m - 1] == 'O') uf.Union(dummy, col * m + m - 1);
    }
    for (int row = 0; row < m; row++) {
      if (board[0][row] == 'O') uf.Union(dummy, row);
      if (board[n - 1][row] == 'O') uf.Union(dummy, m * (n - 1) + row);
    }

    vector<pair<int, int>> actions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };
    int x = 0, y = 0;
    for (int col = 1; col < n - 1; col++) {
      for (int row = 1; row < m - 1; row++) {
        for (auto& p : actions) {
          x = p.first, y = p.second;
          if (board[col][row] == 'O' && board[col + y][row + x] == 'O') {
            uf.Union(get_index(row, col, m), get_index(row + x, col + y, m));
          }
        }
      }
    }

    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        if (board[col][row] == 'O' &&
            !uf.connected(dummy, get_index(row, col, m)))
          board[col][row] = 'X';
      }
    }
  }
};
// @lc code=end

int main() {
  vector<vector<char>> board = {{'X'}};
  // vector<vector<char>> board = {{'X', 'X', 'X', 'X'},
  //                               {'X', 'O', 'O', 'X'},
  //                               {'X', 'X', 'O', 'X'},
  //                               {'X', 'O', 'X', 'X'}};
  Solution s;
  fmt::print("The inputs:\n");
  print2D(board);
  s.solve(board);
  fmt::print("The outputs after solve:\n");
  print2D(board);
  return 0;
}
