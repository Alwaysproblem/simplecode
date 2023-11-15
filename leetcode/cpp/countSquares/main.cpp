/*
 * @lc app=leetcode.cn id=1277 lang=cpp
 *
 * [1277] 统计全为 1 的正方形子矩阵
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
  int countSquares(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix.at(0).size();
    vector<vector<int>> dp(n, vector<int>(m));
    int square_cnt = 0;

    // count the first element once.
    dp.at(0).at(0) = matrix.at(0).at(0);
    square_cnt += dp.at(0).at(0);

    for (int i = 1; i < m; i++) {
      dp.at(0).at(i) = matrix.at(0).at(i);
      square_cnt += dp.at(0).at(i);
    }
    for (int i = 1; i < n; i++) {
      dp.at(i).at(0) = matrix.at(i).at(0);
      square_cnt += dp.at(i).at(0);
    }

    for (int col = 1; col < n; col++) {
      for (int row = 1; row < m; row++) {
        if (matrix.at(col).at(row)) {
          dp.at(col).at(row) =
              min(min(dp.at(col - 1).at(row - 1), dp.at(col).at(row - 1)),
                  dp.at(col - 1).at(row)) +
              1;
        } else {
          dp.at(col).at(row) = 0;
        }
        square_cnt += dp.at(col).at(row);
      }
    }

    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    return square_cnt;
  }
};
// @lc code=end

int main() {
  std::vector<vector<int>> matrix = {{1,0,1},
                                     {1,1,0},
                                     {1,1,0}};
  Solution s;
  int v = s.countSquares(matrix);
  fmt::print("{}\n", v);
  return 0;
}
