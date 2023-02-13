// Note: Dijkstra cpp implementation.
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <climits>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> graph;
  vector<vector<int>> adjacent(int node) {
    vector<vector<int>> adj{};
    for (int i = 1; i < graph[node].size(); i++) {
      if (graph[node][i]) {
        adj.push_back(vector<int>{i, graph[node][i]});
      }
    }
    return adj;
  }

  void relax(vector<int> &cost, vector<int> &prev, int parent, int child,
             int weight) {
    if (cost[parent] + weight < cost[child]) {
      cost[child] = cost[parent] + weight;
      prev[child] = parent;
    }
  }

  void print_path(vector<int> &prev, int target){
    if (!prev.size()) return;
    vector<int> path{};
    int cur = target;
    while (prev[cur] != -1){
      path.push_back(cur);
      cur = prev[cur];
    }
    path.push_back(cur);
    while (path.size()){
      fmt::print("{}", path.back());
      if (path.size() != 1) fmt::print(" -> ");
      path.pop_back();
    }
    fmt::print("\n");
  }

  int networkDelayTime(vector<vector<int>> &times, int n, int k) {
    // setup Graph
    graph.assign(n + 1, vector<int>(n + 1));
    for (vector<int> &x : times) {
      if (x[0] < 1 || x[0] > n) {
        fmt::print("Error!");
        return -1;
      } else if (x[1] < 1 || x[1] > n) {
        fmt::print("Error!");
        return -1;
      } else {
        graph.at(x[0]).at(x[1]) = x[2];
      }
    }
    queue<int> q{};
    vector<int> cost(n + 1, INT_MAX);
    vector<int> prev(n + 1, -1);
    vector<bool> visited(n + 1, false);
    q.emplace(k);
    cost[k] = 0;
    cost[0] = 0;
    int depth = 0;
    int cur = -1;
    int nxt_node = -1;
    int nxt_weight = INT_MAX;
    while (!q.empty()) {
      int sz = q.size();
      for (int j = 0; j < sz; j++) {
        cur = q.front();
        q.pop();
        visited[cur] = true;
        for (vector<int> &nxt : adjacent(cur)) {
          nxt_node = nxt[0];
          nxt_weight = nxt[1];
          if (!visited[nxt_node]) {
            q.emplace(nxt_node);
          }
          relax(cost, prev, cur, nxt_node, nxt_weight);
        }
      }
      depth++;
    }
    fmt::print("{}\n", cost);
    fmt::print("{}\n", prev);
    print_path(prev, 4);
    return -1;
  }
};

int main() {
  vector<vector<int>> times = {{2, 1, 1}, {2, 3, 1}, {3, 4, 9}};
  int n = 4, k = 2;
  Solution s;
  int res = s.networkDelayTime(times, n, k);
  fmt::print("{}\n", res);
  return 0;
}
