/*
 * @lc app=leetcode.cn id=207 lang=cpp
 *
 * [207] 课程表
 * title: course-schedule
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

  void hasCycle_dfs(vector<vector<int>>& graph, int s, vector<bool>& visited,
                    vector<bool>& onPath, bool& has_cycle) {
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
      hasCycle_dfs(graph, node, visited, onPath, has_cycle);
    }

    // 当前节点访问结束,移出路径
    onPath[s] = false;
  }

  bool canFinish_DFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    vector<bool> visited(numCourses, false);
    vector<bool> onPath(numCourses, false);
    bool has_cycle = false;

    buildGraph(graph, numCourses, prerequisites);

    for (int i = 0; i < numCourses; i++) {
      if (!visited[i]) hasCycle_dfs(graph, i, visited, onPath, has_cycle);
    }

    return !has_cycle;
  }

  bool hasCycle_bfs(vector<vector<int>>& graph) {
    vector<int> inDegree(graph.size(), 0);
    for (auto& neighbors : graph) {
      for (int neighbor : neighbors) {
        inDegree[neighbor]++;
      }
    }

    queue<int> q;
    unordered_set<int> visited;
    for (int i = 0; i < inDegree.size(); i++) {
      if (inDegree[i] == 0) {
        q.push(i);
        visited.insert(i);
      }
    }

    int count = 0;
    while (!q.empty()) {
      int node = q.front();
      q.pop();
      count++;
      for (int neighbor : graph[node]) {
        if (!visited.count(neighbor)) {
          inDegree[neighbor]--;
          if (inDegree[neighbor] == 0) {
            q.push(neighbor);
            visited.insert(neighbor);
          }
        }
      }
    }
    return count == graph.size();
  }

  bool canFinish_BFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph{};
    buildGraph(graph, numCourses, prerequisites);
    return hasCycle_bfs(graph);
  }

  bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    const string mode = "BFS";
    if (mode == "DFS")
      return canFinish_DFS(numCourses, prerequisites);
    else
      return canFinish_BFS(numCourses, prerequisites);
  }
};

// @lc code=end

int main() {
  // unordered_map<int, int> v{{1, 3}, {2, 4}, {3, NULL}};
  Solution sol;
  vector<vector<int>> prerequisites{{1, 0}};
  int numCourses = 2;
  bool v = sol.canFinish(numCourses, prerequisites);
  fmt::print("{}\n", v);
  return 0;
}
