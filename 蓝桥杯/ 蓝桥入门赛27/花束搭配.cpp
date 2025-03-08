//https://www.lanqiao.cn/problems/20268/learning/?contest_id=249
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
map<int, int> mp;
int id = 1;
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    
    vector<pair<int, int>> c;
    for(int i = 0; i < n; i++) {
        int x = a[i] - b[i];
        int y = b[i] - a[i];
        c.push_back({x, 0});
        c.push_back({y, 1});
        //cout << x << "   |" << y << endl;
    }
    long long ans = 0;
    sort(c.begin(), c.end());
    int cnt = 0;
    for(int i = 0; i < c.size(); i++) {
        int j = i;
        int one = 0;
        while(j < c.size() && c[j].first == c[i].first) {
            if(c[j].second == 0) {
                ans += cnt;
            } else {
                one++;
            }
            j++;
        }
        //cout << i << " " << j - 1 << " " << cnt << endl;
        i = j - 1;
        cnt += one;
    }
    
    for(int i = 0; i < n; i++) {
        int x = a[i] - b[i];
        int y = b[i] - a[i];
        if(x > y) ans--;
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
