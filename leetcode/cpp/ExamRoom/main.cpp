/*
 * @lc app=leetcode.cn id=855 lang=cpp
 *
 * [855] 考场就座
 * title: exam-room
 */

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// @lc code=start
// https://github.com/Alwaysproblem/fucking-algorithm/blob/master/%E9%AB%98%E9%A2%91%E9%9D%A2%E8%AF%95%E7%B3%BB%E5%88%97/%E5%BA%A7%E4%BD%8D%E8%B0%83%E5%BA%A6.md
/*
 * The idea of this is find the longest the duration.
 * The middle point of that duration is seat allocated.
 * when students leave, the duration ends with this student
 * and that starts with the student should merge into one.
 * 
 * -1 []  []  []  []  []  []  []  []  []  [] 10
 *    0   1   2   3   4   5   6   7   8   9
 * 
 * 0: we add -1 and 10.
 * 1: we choose 0.
 * 2: we choose the end of [0 - 10], 9.
 * 3: we choost the middle of [0 - 9], (9 - 0) // 2 + 0 = 4
 * 4: we have the [0 - 4] and [4 - 9]. sort with (4 - 0) // 2 == (9 - 4) // 2 because it equal so we choose the smaller index, 2.
 * 5: we have the [0 - 2], [2 - 4], [4 - 9] and sort with (y - x) // 2. [4 - 9][0 - 2][2 - 4] and find the largest and cut the middle, 5.
 * 6: if student 4 leaving, [0 - 2], [2 - 4], [4 - 5], [5 - 9]. it will be [0 - 2], [2 - 5], [5 - 9].
 * 
 * 
 * NB:
 * if x == -1 then the distance return y
 * if y == N(10 in example above) then the distance return N - 1 - x.
 * In cpp, the key_compare object must be not changed.
 * so we push the N at last of vector.
 */
class ExamRoom {
 public:
  struct Compare {
    bool operator()(const vector<int>& n1, const vector<int>& n2) const {
      int distA = distance(n1);
      int distB = distance(n2);
      if (distA == distB) return n1[0] < n2[0];
      // the larger distance will be in the front.
      return distA > distB;
    }
  };
  unordered_map<int, vector<int>> startsMap;
  unordered_map<int, vector<int>> endsMap;
  set<vector<int>, Compare> pq;
  int N;

  ExamRoom(int n) : startsMap(), endsMap(), pq(), N(n) {
    addInterval({-1, N, N});
    // fmt::print("{}\n", startsMap);
    // fmt::print("{}\n", endsMap);
    // fmt::print("{}\n", pq);
  }

  void addInterval(vector<int>&& intv) {
    if (!intv.size()) {
      cout << "addInterval: intv size = 0" << endl;
    }
    pq.emplace(intv);
    startsMap[intv[0]] = intv;
    endsMap[intv[1]] = intv;
    // fmt::print("addInterval\n");
    // fmt::print("{}\n", startsMap);
    // fmt::print("{}\n", endsMap);
    // fmt::print("{}\n", pq);
  }

  void addInterval(vector<int>& intv) { addInterval(std::move(intv)); }

  void removeInterval(vector<int>& intv) {
    return removeInterval(std::move(intv));
  }

  void removeInterval(vector<int>&& intv) {
    if (!intv.size()) {
      cout << "removeInterval: intv size = 0" << endl;
    }
    startsMap.erase(intv[0]);
    endsMap.erase(intv[1]);
    pq.erase(intv);
    // fmt::print("removeInterval\n");
    // fmt::print("{}\n", startsMap);
    // fmt::print("{}\n", endsMap);
    // fmt::print("{}\n", pq);
  }

  static int distance(const vector<int>& intv) {
    int x = intv[0];
    int y = intv[1];
    if (x == -1) return y;
    // record the N since the campare object is
    // constant after declaration.
    if (y == intv[2]) return intv[2] - 1 - x;
    return (y - x) / 2;
  }

  int seat() {
    // fmt::print("allocated seat:\n");
    vector<int> longest = *(pq.begin());
    int seat_pos = -1;
    int x = longest[0];
    int y = longest[1];
    removeInterval(longest);
    if (x == -1) {
      seat_pos = 0;
    } else if (y == N) {
      seat_pos = N - 1;
    } else {
      seat_pos = x + (y - x) / 2;
    }
    addInterval({x, seat_pos, N});
    addInterval({seat_pos, y, N});
    return seat_pos;
  }

  void leave(int p) {
    // fmt::print("{} is leaving:\n", p);
    if (startsMap.find(p) == startsMap.end() &&
        endsMap.find(p) == endsMap.end()) {
      // fmt::print(
      // "{} can not be found in"
      // " both startsMap, endsMap\n",
      // p);
      return;
    }
    auto s = startsMap.find(p)->second;
    auto e = endsMap.find(p)->second;
    int y = s[1];
    int x = e[0];
    // fmt::print("s: {}\n", s);
    // fmt::print("e: {}\n", e);
    removeInterval(s);
    removeInterval(e);
    addInterval({x, y, N});
    // fmt::print("Done\n", p);
  }
};
// @lc code=end

int main() {
  // vector<string> actions = {
  //     "ExamRoom", "seat", "seat", "seat", "leave", "leave", "seat", "seat",
  //     "seat",     "seat", "seat", "seat", "seat",  "seat",  "seat", "leave"};
  // vector<vector<int>> param = {{10}, {}, {}, {}, {0}, {4}, {}, {},
  //                              {},   {}, {}, {}, {},  {},  {}, {0}};
  vector<string> actions = {"ExamRoom", "seat",  "seat", "seat",
                            "seat",     "leave", "seat"};
  vector<vector<int>> param = {{10}, {}, {}, {}, {}, {4}, {}};
  // vector<string> actions = {"ExamRoom", "seat", "seat", "seat", "leave",
  //                           "leave",    "seat", "seat", "seat", "seat",
  //                           "seat",     "seat", "seat"};
  // vector<vector<int>> param = {{8}, {}, {}, {}, {0}, {7}, {},
  //                              {},  {}, {}, {}, {},  {}};
  ExamRoom exam(param[0][0]);
  vector<int> res{-1};
  for (int i = 1; i < actions.size(); i++) {
    if (actions[i] == "seat") {
      int s = exam.seat();
      res.push_back(s);
      fmt::print("seat: {}\n", s);
    } else if (actions[i] == "leave") {
      exam.leave(param[i][0]);
      res.push_back(-1);
    }
  }
  fmt::print("res: {}\n", res);
}
