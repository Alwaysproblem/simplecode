#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> res={};
    unordered_map<int, int> visited;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<int> s{};
        for (int i : nums) visited[i] ++;
        std::sort(nums.begin(), nums.end());
        backtrack(nums, s, visited);
        return res;
    }

    void backtrack(vector<int>& nums, vector<int> solution, unordered_map<int, int> visited) {
        if (solution.size() == nums.size()) {
            res.push_back(solution);
            return;
        }

        for (int j=0; j < nums.size(); ++j) {
          if 	(visited[nums[j]] == 0 || j > 0 && nums[j-1] == nums[j]) continue;
          visited[nums[j]] --;
          solution.push_back(nums[j]);
          backtrack(nums, solution, visited);
          solution.pop_back();
          visited[nums[j]] ++;
        }
    }
};

int main()
{
  Solution s;
  vector<int> v{1,1,2};
  vector<vector<int>> result = s.permuteUnique(v);
  cout << "[" ;
  for (auto& i : result)
  {
    cout << "[" ;
    for (auto& j : i)
    {
      cout << j << " ";
    }
    cout << "] ";
  }
  cout << "] " << endl;
  return 0;
}
