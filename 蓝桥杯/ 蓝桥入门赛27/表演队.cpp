//https://www.lanqiao.cn/problems/20267/learning/?contest_id=249
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
const ll INF = 1e18;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);

    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    long long ans = INF;
    long long add = 0;
    long long sub = 0;
    long long s = 0;
    for(int i = 0; i < n; i++) {
        if(i + 1 <= k) {
            s += a[i];
            add += ((a[i] + 0ll) * (i + 1));
            sub += ((a[i] + 0ll) * (k - i));
        } else {
            add += ((a[i] + 0ll) * k);
            add -= (s);
            sub += (a[i]);
            sub += (s - a[i - k]);
            sub -= ((a[i - k] + 0ll) * k);
            s += a[i];
            s -= a[i - k];
        }
        
        //cout << i << "  " << s << "    |" << add << "  " << sub << endl;

        if(i + 1 >= k) {
            ans = min(ans, add - sub);
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
