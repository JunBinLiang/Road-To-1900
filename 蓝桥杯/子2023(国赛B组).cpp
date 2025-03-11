//https://www.lanqiao.cn/problems/17104/learning/?page=1&first_category_id=1&second_category_id=3&name=%E5%AD%902023
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <queue>    
#include <deque>  

using namespace std;

#define ve vector
#define pb push_back
#define FOR(i, a, b) for (int i = a; i < b; ++i)
using ll = long long;

void solve() {
    string s = "";
    for(int i = 1; i <= 2023; i++) s += to_string(i);
    string t = "2023";
    vector<vector<long long>> dp(s.size(), vector<long long>(4));
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '2') {
            dp[i][0]++;
        }

        for(int j = 1; j < 4; j++) {
            if(s[i] == t[j]) {
                dp[i][j] += dp[i - 1][j - 1];
            }
        }

        for(int j = 0; j < 4; j++) {
            if(i) {
                dp[i][j] += dp[i - 1][j];
            }
        }
    }
    cout << dp.back()[3];
}

int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
