//https://www.lanqiao.cn/problems/17153/learning/?page=1&first_category_id=1&second_category_id=3&name=%E7%8F%AD%E7%BA%A7%E6%B4%BB%E5%8A%A8
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
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    map<int, int> mp;
    for(int x : a) mp[x]++;
    int cnt = 0, more = 0;
    int ans = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        int cnt = it -> second;
        if(cnt == 2) continue;
        else if(cnt > 2) {
            more += (cnt - 2);
        }
    }
    int less = 0;
    for(auto it = mp.begin(); it != mp.end(); it++) {
        int cnt = it -> second;
        if(cnt == 2) continue;
        else if(cnt < 2) {
            if(more) {
                more--;
                ans++;
            } else {
                less++;
            }
        }
    }
    ans += more;
    ans += (less / 2);
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
