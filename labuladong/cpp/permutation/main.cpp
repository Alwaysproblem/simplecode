#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> res={};
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> s{};
        backtrack(nums, s);
        return res;
    }

    void backtrack(vector<int>& nums, vector<int> solution) {
        if (solution.size() == nums.size()) {
            res.push_back(solution);
            return;
        }
        for (int c : nums){
            if (std::find(solution.begin(), solution.end(), c) != solution.end()) continue;
            solution.push_back(c);
            backtrack(nums, solution);
            solution.pop_back();
        }
    }
};

int main()
{
  Solution s;
  vector<int> v{1, 2, 3};
  vector<vector<int>> result = s.permute(v);
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
