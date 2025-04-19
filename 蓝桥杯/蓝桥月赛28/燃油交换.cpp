//https://www.lanqiao.cn/problems/20311/learning/?contest_id=254
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

long long cal(vector<long long> a, vector<long long> b) {
    int n = a.size();
    long long ans = 1e18;
    long long tot = 0, s = 0;
    for(long long x : b) tot += x;
    for(int i = 0; i < n; i++) {
        tot -= b[i];
        s += a[i];
        ans = min(ans, s + tot);
    }
    return ans;
}

void solve() {
    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    long long ans = 1e18;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];


    ans = min(ans, cal(a, b));
    ans = min(ans, cal(b, a));
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
