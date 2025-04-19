//https://www.lanqiao.cn/problems/20312/learning/?contest_id=254
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
    int n, d;
    cin >> n >> d;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> s;
    int ans = 0;
    for(int i = 0; i < n; i++) {
        if(s.find(a[i]) != s.end()) continue;
        s.insert(a[i] + d);
        ans++;
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
