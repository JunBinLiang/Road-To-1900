//https://www.lanqiao.cn/problems/20270/learning/?contest_id=250
#include <iostream>
#include <cstring>
#include <algorithm>
#include <bitset>
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
    string s;
    cin >> s;
    string t = "lan";
    int n = s.size();
    vector<vector<long long>> dp(n, vector<long long>(3));
    for(int i = 0; i < s.size(); i++) {
        for(int j = 0; j < t.size(); j++) {
            if(s[i] == t[j]) {
                if(j == 0) dp[i][j] = 1;
                else {
                    if(i) dp[i][j] += dp[i - 1][j - 1];
                }
            }
            if(i) dp[i][j] += dp[i - 1][j];
        }
    }
    cout << dp[n - 1][2] << endl;
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
