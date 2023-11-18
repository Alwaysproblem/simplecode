/*
 * @lc app=leetcode.cn id=200 lang=cpp
 *
 * [200] 岛屿数量
 * title: number-of-islands
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

  vector<int> get_parent() const { return parent; }

 private:
  int count;
  vector<int> parent;
};

class Solution {
 public:
  // -------------DFS----------------
  void dfs(vector<vector<char>>& grid, int i, int j,
           vector<vector<bool>>& visited) {
    int n = grid.size();
    int m = grid[0].size();

    if (i < 0 || j < 0 || j >= n || i >= m) return;
    if (visited[j][i]) return;
    if (grid[j][i] == '0') return;

    visited[j][i] = true;

    vector<pair<int, int>> actions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };

    int x = 0, y = 0;
    for (auto& p : actions) {
      x = p.first, y = p.second;
      dfs(grid, i + x, j + y, visited);
    }
  }

  int numIslands(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<bool>> visited(n, vector<bool>(m));
    int cnt = 0;
    for (int row = 0; row < n; row++) {
      for (int col = 0; col < m; col++) {
        if (!visited[row][col] && grid[row][col] == '1') {
          dfs(grid, col, row, visited);
          cnt++;
        }
      }
    }

    // print2D(visited);
    return cnt;
  }

  // -------------Union Find-----------------
  int get_index(int row, int col, int m) { return col * m + row; }

  char get_value(vector<vector<char>>& grid, int i, int j) {
    int n = grid.size();
    int m = grid[0].size();
    if (i < 0 || i >= n) return '0';
    if (j < 0 || j >= m) return '0';
    return grid[i][j];
  }

  int numIslands_with_uf(vector<vector<char>>& grid) {
    int n = grid.size();
    int m = grid[0].size();
    UnionFind uf{n * m};
    vector<pair<int, int>> actions = {
        {-1, 0},
        {0, -1},
        {1, 0},
        {0, 1},
    };

    // collect the count number about single 1.
    // UnionFind can only find the multiple 1.
    // like this:
    //   0
    // 0 1 0
    //   0
    int single_1_count = 0;
    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        if (get_value(grid, col, row) == '1' &&
            get_value(grid, col - 1, row) == '0' &&
            get_value(grid, col, row - 1) == '0' &&
            get_value(grid, col + 1, row) == '0' &&
            get_value(grid, col, row + 1) == '0') {
          single_1_count++;
        }
      }
    }

    int x = 0, y = 0;
    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        for (auto& p : actions) {
          x = p.first, y = p.second;
          if (((row + x) >= 0 && (col + y) >= 0) &&
              ((row + x) < m && (col + y) < n))
            if (grid[col][row] == '1') {
              if (grid[col + y][row + x] == '1') {
                uf.Union(get_index(row, col, m),
                         get_index(row + x, col + y, m));
              }
            }
        }
      }
    }

    // update the parent of UnionFind.
    // this is important for get precise 1 block location.
    vector<vector<int>> board(n, vector<int>(m, -1));
    for (int col = 0; col < n; col++) {
      for (int row = 0; row < m; row++) {
        int idx = get_index(row, col, m);
        board[col][row] = uf.find(idx);
      }
    }

    vector<int> par = uf.get_parent();
    int multi_1_count = 0;
    unordered_map<int, int> counter{};
    for (const int pn : par) {
      counter[pn]++;
    }

    for (auto& c : counter) {
      if (c.second > 1) {
        multi_1_count++;
      }
    }

    // fmt::print("parents: {}\n", par);
    // fmt::print("single 1 count: {}\n", single_1_count);
    // fmt::print("counter: {}\n", counter);
    // fmt::print("multi_1_count: {}\n", multi_1_count);
    // print2D(board);
    // -----------
    //    1 1 1
    //    0 1 0
    //    1 1 1

    //    parents: [6, 6, 6, 3, 6, 5, 6, 6, 6]
    //    single 1 count: 0
    //    counter: {5: 1, 3: 1, 6: 7}
    //    multi_1_count: 1
    //    board:
    //      6 6 6
    //      3 6 5
    //      6 6 6

    return multi_1_count + single_1_count;
  }
};
// @lc code=end

int main() {
  // vector<vector<char>> grid = {
  //     {'1', '1', '1'}, {'0', '1', '0'}, {'1', '1', '1'}};
  // vector<vector<char>> grid = {{'1', '1', '0', '0', '0'},
  //                              {'1', '1', '0', '0', '0'},
  //                              {'0', '0', '1', '0', '0'},
  //                              {'0', '0', '0', '1', '1'}};
  vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                               {'1', '1', '0', '1', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '0', '0', '0'}};
  print2D(grid);
  Solution sol;
  auto v = sol.numIslands(grid);
  fmt::print("{}\n", v);
  return 0;
}
