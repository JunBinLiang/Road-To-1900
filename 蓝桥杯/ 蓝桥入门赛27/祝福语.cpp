//https://www.lanqiao.cn/problems/20264/learning/?contest_id=249
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
    string s;
    cin >> s;
    int cnt = 0;
    int mx = 0;
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == 'a') {
            cnt++;
        } else {
            cnt = 0;
        }
        mx = max(mx, cnt);
    }

    string ans = "";
    for(int i = 0; i < mx + 1; i++) {
        ans += 'a';
    }
    cout << ans << endl;
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
