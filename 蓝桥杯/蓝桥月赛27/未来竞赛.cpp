//https://www.lanqiao.cn/problems/20273/learning/?contest_id=250
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

const int MOD = 1e9 + 7;
void solve() {
    int n, d;
    cin >> n >> d;
    vector<int> a(n + 1);
    unordered_map<int, vector<int>> mp;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        mp[a[i]].push_back(i);
    }

    long long ans = 1;

    for(auto it = mp.begin(); it != mp.end(); it++) {
        vector<int>& vec = it -> second;
        long long w = 0;
        int j = 0;
        for(int i = 0; i < vec.size(); i++) {
            while(j < i && vec[i] - vec[j] > d) {
                j++;
            }
            w += (i - j);
        }
        w += vec.size();
        w++;
        //cout << it -> first << " " << w << endl;
        ans *= w;
        ans %= MOD;
    }
    ans -= 1;
    if(ans < 0) ans += MOD;

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
