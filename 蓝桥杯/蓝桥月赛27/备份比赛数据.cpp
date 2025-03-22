https://www.lanqiao.cn/problems/20274/learning/?contest_id=250

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

bool ok(vector<int>& a, vector<int>& b, int mid, int t) {
    int n = a.size();
    int s = 0;
    int day = 1;
    for(int i = 0; i < n; i++) {
        if(s + a[i] > mid) {
            day++;
            s = a[i];
        } else {
            s += a[i];
        }
        
        if(i == n - 1) break;
        s += b[i];
        while(s > mid) {
          s -= mid;
          day++;
        }

        if(s > mid) {
          day += (s / mid);
          s %= 
        }

        
        //if(mid == 5) cout << "gg " << s << " " << day << endl;
    }
    
    return day <= t;
}

void solve() {
    int n, t;
    cin >> n >> t;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    int l = 0;
    for(int i = 0; i < n; i++) {
        l = max(l, a[i]);
    }

    int r = 3600;
    int ans = -1;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(ok(a, b, mid, t)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
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
