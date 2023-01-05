#include <iostream>
#include <unordered_map>
#include <vector>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <queue>
#include <unordered_set>

using namespace std;

class Solution
{
public:
  string plusOne(string current, int j)
  {
    if (current[j] == '9')
      current[j] = '0';
    else
      current[j] += 1;
    return current;
  }

  string minusOne(string current, int j)
  {
    if (current[j] == '0')
      current[j] = '9';
    else
      current[j] -= 1;
    return current;
  }

  int BFS(string start, string target, unordered_set<string> visited)
  {
    queue<string> q;
    visited.insert(start);
    q.push(start);
    int step = 0;

    string cur = "";
    string p = "";
    string m = "";
    while (!q.empty())
    {
      int sz = q.size();
      for (int i = 0; i < sz; ++i)
      {
        cur = q.front();
        q.pop();

        if (cur == target)
        {
          return step;
        }
        for (int i = 0; i <= 3; i++)
        {
          p = plusOne(cur, i);
          if (visited.count(p) == 0){
            q.push(p);
            visited.insert(p);
          }
          m = minusOne(cur, i);
          if (visited.count(m) == 0){
            q.push(m);
            visited.insert(m);
          }
        }
      }
      step++;
    }
    return -1;
  }

  int openLock(vector<string> &deadends, string target)
  {
    unordered_set<string> deadends_set(deadends.begin(), deadends.end());
    if ("0000" == target)
        return 0;

    if (deadends_set.count("0000"))
      return -1;

    return BFS("0000", target, deadends_set);
  }
};

int main()
{
  Solution s;
  vector<string> deadends{"0201","0101","0102","1212","2002"};
  int t = s.openLock(deadends, "0202");
  fmt::print("You need to try at least {} times to open the lock.\n", t);
  return 0;
}
