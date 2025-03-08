//https://www.lanqiao.cn/problems/20266/learning/?contest_id=249
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
    int n;
    string s;
    cin >> n >> s;
    int p = -1;
    vector<int> ans(n, 1000000000);
    for(int i = 0; i < n; i++) {
        if(s[i] == '1') {
            p = i;
        } else {
            if(p != -1)
                ans[i] = abs(i - p);
        }
    }

    p = -1;
    for(int i = n - 1; i >= 0; i--) {
        if(s[i] == '1') {
            p = i;
        } else {
            if(p != -1)
                ans[i] = min(ans[i], abs(i - p));
        }
    }

    if(p == -1) {
        for(int i = 0; i < n; i++) {
            if(s[i] == '0') cout << -1 << " ";
        }
        return;
    }

    for(int i = 0; i < n; i++) {
        if(s[i] == '0') cout << ans[i] << " ";
    }
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
