/*
题意 :
{
  "times": [
    [0, 2],
    [1, 4],
    [4, 6],
    [0, 4],
    [7, 8],
    [9, 11],
    [3, 10]
  ]
}
表示学生laptop rental 时间。找出最少需要多少个laptop 可以给所有学生用。
线扫描
  
*/

#include <vector>
using namespace std;

int laptopRentals(vector<vector<int>> times) {
  // Write your code here.

  map<int, int> mp;
  for(vector<int>& e : times) {
    mp[e[0]]++;
    mp[e[1]]--;
  }

  int s = 0;
  int ans = 0;
  for(auto it = mp.begin(); it != mp.end(); it++) {
    s += it -> second;
    ans = max(ans, s);
  }
  
  return ans;
}
