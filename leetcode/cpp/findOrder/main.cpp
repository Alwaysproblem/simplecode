/*
 * @lc app=leetcode.cn id=210 lang=cpp
 *
 * [210] 课程表 II
 * title: course-schedule-ii
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/debug_print.hpp"

using namespace std;

// @lc code=start
class Solution {
 public:
  void buildGraph(vector<vector<int>>& graph, int numCourses,
                  vector<vector<int>>& prerequisites) {
    graph.resize(numCourses);
    for (auto& edge : prerequisites) {
      int from = edge[1], to = edge[0];
      // 添加一条从 from 指向 to 的有向边
      // 边的方向是「被依赖」关系，即修完课程 from 才能修课程 to
      graph[from].push_back(to);
    }
  }
  void topology_order_dfs(vector<vector<int>>& graph, int s,
                          vector<bool>& visited, vector<bool>& onPath,
                          bool& has_cycle, vector<int>& res) {
    if (onPath[s]) {
      // 发现环
      has_cycle = true;
      return;
    }

    if (visited[s]) {
      // 已访问过,无需再访问
      return;
    }

    // 标记当前节点为已访问
    visited[s] = true;

    // 标记当前节点在路径上
    onPath[s] = true;

    // 递归访问相邻节点
    for (int node : graph[s]) {
      topology_order_dfs(graph, node, visited, onPath, has_cycle, res);
    }

    // 当前节点访问结束,移出路径
    onPath[s] = false;
    res.push_back(s);
  }

  vector<int> findOrder_DFS(int numCourses,
                            vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    vector<bool> visited(numCourses, false);
    vector<bool> onPath(numCourses, false);
    vector<int> res;
    bool has_cycle = false;

    buildGraph(graph, numCourses, prerequisites);
    // print2D(graph);
    for (int i = 0; i < numCourses && !has_cycle; i++) {
      if (!visited[i]) {
        topology_order_dfs(graph, i, visited, onPath, has_cycle, res);
      }
    }

    if (has_cycle) {
      return {};
    }

    reverse(res.begin(), res.end());
    return res;
  }

  vector<int> topology_order_bfs(vector<vector<int>>& graph) {
    vector<int> in_degree(graph.size(), 0);
    for (auto& neighbors : graph) {
      for (int neighbor : neighbors) {
        in_degree[neighbor]++;
      }
    }

    queue<int> q;
    unordered_set<int> visited;
    for (int i = 0; i < in_degree.size(); i++) {
      if (in_degree[i] == 0) {
        q.push(i);
        visited.insert(i);
      }
    }

    vector<int> res;
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      res.push_back(node);
      for (int neighbor : graph[node]) {
        in_degree[neighbor]--;
        if (in_degree[neighbor] == 0) {
          q.push(neighbor);
          visited.insert(neighbor);
        }
      }
    }

    if (res.size() != graph.size()) {
      return {};
    }

    return res;
  }

  vector<int> findOrder_BFS(int numCourses,
                            vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    buildGraph(graph, numCourses, prerequisites);
    return topology_order_bfs(graph);
  }

  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    const string mode = "BFS";
    if (mode == "DFS")
      return findOrder_DFS(numCourses, prerequisites);
    else
      return findOrder_BFS(numCourses, prerequisites);
  }
};
// @lc code=end

int main() {
  // unordered_map<int, int> v{{1, 3}, {2, 4}, {3, NULL}};
  Solution sol;
  vector<vector<int>> prerequisites{};
  int numCourses = 2;
  vector<int> v = sol.findOrder(numCourses, prerequisites);
  fmt::print("{}\n", v);
  return 0;
}
