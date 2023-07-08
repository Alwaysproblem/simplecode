#include <fmt/format.h>
#include <fmt/ranges.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
 public:
  enum Choice { INSERT = 0, REPLACE, DELETE, SKIP };

  int record_action(int deletion, int insertion, int replacement) {
    Choice c = Choice::DELETE;
    if (deletion > insertion) {
      c = Choice::INSERT;
    }
    if (deletion > replacement) {
      c = Choice::REPLACE;
    }
    return c;
  }

  void print_solution(const string word1, const string word2,
                      vector<vector<int>>& action) {
    unordered_map<int, string> action_print_table{{Choice::INSERT, "INSERT"},
                                                  {Choice::REPLACE, "REPLACE"},
                                                  {Choice::DELETE, "DELETE"},
                                                  {Choice::SKIP, "SKIP"}};
    int row = word2.size();
    int col = word1.size();
    vector<pair<string, char>> action_order{};
    string a = "";
    while (row > 0 && col > 0) {
      if (action[row][col] == Choice::SKIP) {
        // fmt::print("{} ", action_print_table[action[row][col]]);
        row--;
        col--;
      } else if (action[row][col] == Choice::REPLACE) {
        // fmt::print("{} ", action_print_table[action[row][col]]);
        action_order.push_back(make_pair("replace", word1[col - 1]));
        row--;
        col--;
      } else if (action[row][col] == Choice::DELETE) {
        // fmt::print("{} ", action_print_table[action[row][col]]);
        action_order.push_back(make_pair("delete", word1[col - 1]));
        col--;
      } else if (action[row][col] == Choice::INSERT) {
        // fmt::print("{} ", action_print_table[action[row][col]]);
        action_order.push_back(make_pair("insert", word1[col - 1]));
        row--;
      }
      // fmt::print("{}\n", word1[col]);
    }
    if (row == 0 && col != 0) {
      while (col > 0) {
        action_order.push_back(make_pair("delete", word1[col - 1]));
        col--;
      }
    } else if (row != 0 && col == 0) {
      while (row > 0) {
        action_order.push_back(make_pair("insert", word2[row - 1]));
        row--;
      }
    }

    reverse(action_order.begin(), action_order.end());
    for (auto& p : action_order) {
      fmt::print("action: {}, target: {}\n", p.first, p.second);
    }
  }

  int minDistance(string word1, string word2) {
    vector<vector<int>> dp(word2.size() + 1, vector<int>(word1.size() + 1));
    vector<vector<int>> actions(word2.size() + 1,
                                vector<int>(word1.size() + 1));
    Choice c;
    for (int i = 1; i <= word1.size(); i++) {
      dp[0][i] = i;
      actions[0][i] = Choice::DELETE;
    }
    for (int i = 1; i <= word2.size(); i++) {
      dp[i][0] = i;
      actions[i][0] = Choice::INSERT;
    }
    for (int row = 1; row <= word2.size(); row++) {
      for (int col = 1; col <= word1.size(); col++) {
        if (word2[row - 1] == word1[col - 1]) {
          dp[row][col] = dp[row - 1][col - 1];  // skip
          actions[row][col] = Choice::SKIP;     // skip
        } else {
          dp[row][col] = min(min(dp[row - 1][col],       // insertion
                                 dp[row - 1][col - 1]),  // replacement
                             dp[row][col - 1]            // deletion
                             ) +
                         1;

          actions[row][col] = record_action(dp[row][col - 1], dp[row - 1][col],
                                            dp[row - 1][col - 1]);
        }
      }
    }
    // fmt::print("{}\n", fmt::join(dp.begin(), dp.end(), "\n"));
    // cout << "the action mapping is 0 -> insertion, 2 -> deletion, 1 -> "
    //         "replacement, 3 -> skip."
    //      << endl;
    // fmt::print("{}\n", fmt::join(actions.begin(), actions.end(), "\n"));
    print_solution(word1, word2, actions);
    return dp.back().back();
  }
};

int main() {
  string word1 = "fucking", word2 = "funk";
  Solution sol;
  int v = sol.minDistance(word1, word2);
  fmt::print("{}\n", v);
  return 0;
}
