#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void printNestedVector(vector<vector<T>> &arr) {
  cout << "[" ;
  for (auto& i : arr)
  {
    cout << "[" ;
    for (auto& j : i)
    {
      cout << j << " ";
    }
    cout << "] ";
  }
  cout << "] " << endl;
}

template<typename T>
void printVector(vector<T> &arr) {
  cout << "[" ;
  for (auto& i : arr)
  {
      cout << i << " ";
  }
  cout << "] " << endl;
}

class Solution {
public:
    vector<vector<int>> res{};
    map<int, int> visited{};
    vector<vector<int>> subsets(vector<int>& nums) {
      vector<int> s{};
      for (int i: nums) visited[i] = 0;
      int empty_set = *min_element(nums.begin(), nums.end()) - 1;
      cout << empty_set << endl;
      backtrack(nums, s, visited, empty_set);
      return res;
    }

    void backtrack(vector<int>& nums, vector<int>& solution, map<int, int> visited, int empty_set) {
      if (!solution.empty() && solution.back() == empty_set) {
        printVector(solution);
        solution.pop_back();
        if (solution.size() <= visited.size()) res.push_back(solution);
        solution.push_back(empty_set);
        return;
      }

      for (int ix = -1; ix < int(nums.size()); ++ix) {
        if (ix < 0){
          solution.push_back(empty_set);
          backtrack(nums, solution, visited, empty_set);
          solution.pop_back();
        }
        else{
          cout << "ix: " << ix << endl;
          cout << "numx" << nums[ix] << endl;
          if (visited[nums[ix]] != 0)
            continue;
          solution.push_back(nums[ix]);
          visited[nums[ix]] = 1;
          backtrack(nums, solution, visited, empty_set);
          visited[nums[ix]] = 0;
          solution.pop_back();
          visited[nums[ix]] = 1;
        }
      }
    }
};

int main()
{
  Solution s;
  vector<int> v{1, 2, 3};
  vector<vector<int>> result = s.subsets(v);
  printNestedVector<int>(result);
  return 0;
}
