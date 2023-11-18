/*
 * @lc app=leetcode.cn id=743 lang=cpp
 *
 * [743] 网络延迟时间
 * title: network-delay-time
 */
// Note: Dijkstra cpp implementation.
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void print_path(vector<int> &prev, int target) {
  if (!prev.size()) return;
  vector<int> path{};
  int cur = target;
  while (prev[cur] != -1) {
    path.push_back(cur);
    cur = prev[cur];
  }
  path.push_back(cur);
  while (path.size()) {
    fmt::print("{}", path.back());
    if (path.size() != 1) fmt::print(" -> ");
    path.pop_back();
  }
  fmt::print("\n");
}

// @lc code=start
class Solution {
 public:
  vector<vector<int>> graph;
  vector<vector<int>> adjacent(int node) {
    vector<vector<int>> adj{};
    for (int i = 1; i < graph[node].size(); i++) {
      if (graph[node][i] != -1) {
        adj.push_back(vector<int>{i, graph[node][i]});
      }
    }
    return adj;
  }

  void relax(vector<int> &cost, vector<int> &prev, int parent, int child,
             int weight) {
    cost[child] = cost[parent] + weight;
    prev[child] = parent;
  }

  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    // setup Graph
    graph.assign(n + 1, vector<int>(n + 1, -1));
    for (vector<int> &x : times) {
      if (x[0] < 1 || x[0] > n) {
        // fmt::print("Error!");
        return -1;
      } else if (x[1] < 1 || x[1] > n) {
        // fmt::print("Error!");
        return -1;
      } else {
        graph.at(x[0]).at(x[1]) = x[2];
      }
    }
    queue<int> q{};
    vector<int> cost(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);
    // vector<bool> visited(n + 1, false);
    unordered_set<int> visited{};
    q.emplace(k);
    cost[k] = 0;
    cost[0] = 0;
    int depth = 0;
    int cur = -1;
    int nxt_node = -1;
    int nxt_weight = INT_MAX;
    while (visited.size() <= n && !q.empty()) {
      int sz = q.size();
      for (int j = 0; j < sz; j++) {
        cur = q.front();
        q.pop();
        // visited[cur] = true;
        visited.insert(cur);
        for (vector<int> &nxt : adjacent(cur)) {
          nxt_node = nxt[0];
          nxt_weight = nxt[1];
          if (cost[cur] + nxt_weight < cost[nxt_node]) {
            relax(cost, prev, cur, nxt_node, nxt_weight);
            q.emplace(nxt_node);
          }
        }
      }
      depth++;
    }
    // fmt::print("{}\n", cost);
    // fmt::print("{}\n", prev);
    // print_path(prev, 3);
    for (int j = 1; j < prev.size(); j++) {
      if (j != k && prev[j] == -1) return -1;
    }
    int max_val = 0;
    for (int j : cost) {
      if (j != INT_MAX && j > max_val) max_val = j;
    }
    return max_val;
  }
};
// @lc code=end

int main() {
  // vector<vector<int>> times = {{1, 2, 1}};
  // vector<vector<int>> times = {{1, 2, 1}, {2, 3, 2}, {1, 3, 1}};
  // vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
  // int n = 4, k = 2;
  // vector<vector<int>> times = {{3, 5, 78}, {2, 1, 1},  {1, 3, 0},  {4, 3,
  // 59},
  //                              {5, 3, 85}, {5, 2, 22}, {2, 4, 23}, {1, 4,
  //                              43}, {4, 5, 75}, {5, 1, 15}, {1, 5, 91}, {4,
  //                              1, 16}, {3, 2, 98}, {3, 4, 22}, {5, 4, 31},
  //                              {1, 2, 0}, {2, 5, 4},  {4, 2, 51}, {3, 1, 36},
  //                              {2, 3, 59}};
  vector<vector<int>> times = {
      {15, 8, 1},   {7, 10, 41},  {7, 9, 34},   {9, 4, 31},   {12, 13, 50},
      {14, 3, 52},  {4, 11, 99},  {4, 7, 86},   {10, 13, 57}, {9, 6, 10},
      {1, 7, 51},   {7, 15, 38},  {1, 9, 11},   {12, 7, 94},  {9, 13, 34},
      {11, 7, 79},  {7, 6, 28},   {5, 3, 34},   {2, 6, 97},   {14, 1, 97},
      {6, 10, 90},  {12, 10, 37}, {13, 3, 73},  {11, 14, 7},  {15, 1, 39},
      {6, 5, 90},   {13, 6, 43},  {6, 9, 32},   {4, 6, 45},   {11, 10, 2},
      {2, 13, 4},   {14, 15, 29}, {1, 14, 88},  {14, 6, 19},  {6, 2, 29},
      {3, 14, 72},  {1, 15, 4},   {11, 5, 2},   {6, 7, 56},   {8, 7, 88},
      {13, 14, 70}, {14, 12, 58}, {14, 2, 86},  {11, 3, 57},  {5, 2, 56},
      {3, 10, 26},  {2, 11, 21},  {14, 5, 54},  {5, 12, 40},  {14, 4, 81},
      {15, 2, 99},  {5, 7, 57},   {13, 12, 5},  {4, 9, 60},   {12, 15, 48},
      {6, 14, 1},   {9, 7, 44},   {13, 7, 69},  {5, 13, 42},  {4, 1, 7},
      {11, 9, 76},  {8, 1, 76},   {5, 14, 29},  {2, 3, 69},   {7, 3, 23},
      {12, 14, 28}, {11, 4, 85},  {10, 1, 10},  {15, 12, 36}, {1, 11, 69},
      {15, 10, 96}, {11, 13, 69}, {7, 12, 49},  {1, 2, 95},   {6, 4, 46},
      {8, 12, 94},  {12, 4, 93},  {13, 5, 31},  {12, 2, 60},  {6, 1, 87},
      {4, 14, 20},  {5, 11, 89},  {4, 15, 88},  {4, 10, 21},  {1, 6, 5},
      {10, 8, 26},  {8, 2, 51},   {3, 15, 23},  {7, 2, 12},   {11, 1, 47},
      {2, 1, 75},   {3, 8, 63},   {8, 10, 19},  {6, 8, 18},   {4, 2, 55},
      {14, 11, 80}, {10, 3, 73},  {3, 5, 22},   {12, 3, 61},  {1, 13, 33},
      {9, 3, 98},   {9, 12, 69},  {15, 9, 6},   {7, 13, 76},  {11, 12, 22},
      {11, 15, 51}, {13, 15, 46}, {5, 10, 58},  {1, 10, 26},  {13, 4, 85},
      {7, 14, 58},  {5, 8, 46},   {11, 6, 32},  {10, 9, 41},  {9, 14, 35},
      {14, 13, 60}, {3, 9, 97},   {2, 5, 39},   {7, 11, 19},  {1, 12, 27},
      {7, 5, 13},   {8, 4, 34},   {9, 15, 25},  {5, 1, 93},   {15, 13, 97},
      {14, 9, 35},  {8, 6, 67},   {9, 5, 39},   {13, 11, 35}, {7, 4, 21},
      {12, 9, 64},  {14, 8, 8},   {10, 12, 94}, {8, 9, 76},   {8, 5, 71},
      {2, 9, 64},   {10, 14, 59}, {1, 4, 74},   {7, 1, 69},   {15, 5, 55},
      {6, 15, 80},  {13, 8, 84},  {8, 13, 63},  {8, 3, 91},   {10, 4, 87},
      {1, 5, 39},   {8, 11, 0},   {1, 3, 79},   {4, 5, 82},   {4, 12, 87},
      {3, 11, 29},  {7, 8, 92},   {10, 7, 77},  {6, 12, 42},  {13, 2, 40},
      {9, 10, 13},  {4, 13, 65},  {2, 4, 34},   {3, 13, 44},  {2, 14, 69},
      {3, 4, 42},   {5, 15, 98},  {14, 7, 6},   {15, 3, 94},  {10, 2, 37},
      {15, 11, 7},  {9, 2, 15},   {13, 9, 66},  {4, 8, 83},   {8, 15, 23},
      {13, 1, 50},  {6, 13, 57},  {2, 10, 37},  {10, 6, 38},  {2, 7, 45},
      {9, 8, 8},    {3, 12, 28},  {3, 2, 83},   {2, 12, 75},  {1, 8, 91},
      {4, 3, 70},   {12, 6, 48},  {3, 1, 13},   {5, 6, 42},   {6, 11, 96},
      {3, 6, 22},   {15, 6, 34},  {11, 8, 43},  {15, 7, 40},  {9, 11, 57},
      {11, 2, 11},  {2, 8, 22},   {9, 1, 73},   {2, 15, 40},  {12, 11, 10},
      {15, 4, 78},  {12, 8, 75},  {10, 15, 37}, {13, 10, 44}, {8, 14, 33},
      {3, 7, 82},   {5, 4, 46},   {12, 5, 79},  {15, 14, 43}, {10, 5, 65},
      {5, 9, 34},   {12, 1, 54},  {6, 3, 16},   {14, 10, 83}, {10, 11, 67}};
  int n = 15, k = 11;
  Solution s;
  int res = s.networkDelayTime(times, n, k);
  fmt::print("{}\n", res);
  return 0;
}
