/*
 * @lc app=leetcode.cn id=221 lang=cpp
 *
 * [221] 最大正方形
 * title: maximal-square
 */
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int n = matrix.size();
    int m = matrix.at(0).size();
    vector<vector<int>> dp(n, vector<int>(m));
    int max_value = 0;

    for (int i = 0; i < m; i++) {
      dp.at(0).at(i) = matrix.at(0).at(i) - '0';
      max_value = max_value < dp.at(0).at(i) ? dp.at(0).at(i) : max_value;
    }
    for (int i = 0; i < n; i++) {
      dp.at(i).at(0) = matrix.at(i).at(0) - '0';
      max_value = max_value < dp.at(i).at(0) ? dp.at(i).at(0) : max_value;
    }

    for (int col = 1; col < n; col++) {
      for (int row = 1; row < m; row++) {
        if (matrix.at(col).at(row) - '0') {
          dp.at(col).at(row) =
              min(min(dp.at(col - 1).at(row - 1), dp.at(col).at(row - 1)),
                  dp.at(col - 1).at(row)) +
              1;
        } else {
          dp.at(col).at(row) = 0;
        }
        max_value =
            max_value < dp.at(col).at(row) ? dp.at(col).at(row) : max_value;
      }
    }

    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return max_value * max_value;
  }
};
// @lc code=end

int main() {
  std::vector<vector<char>> matrix = {{
                                          '0',
                                          '1',
                                      },
                                      {
                                          '1',
                                          '0',
                                      }};
  // std::vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'},
  //                                     {'1', '0', '1', '1', '1'},
  //                                     {'1', '1', '1', '1', '1'},
  //                                     {'1', '0', '0', '1', '0'}};
  Solution s;
  int v = s.maximalSquare(matrix);
  fmt::print("{}\n", v);
  return 0;
}
