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
const int N = 1e5 + 10;
int cnt[N];

void solve() {
    int n;
    cin >> n;
    memset(cnt, 0, sizeof cnt);
    for(int i = 0; i < n; i++) {
      int x;
      cin >> x;
      cnt[x]++;
    }
    //最大化 gcd(a, b, c)
    for(int g = N - 1; g >= 1; g--) {
      vector<int> a;
      for(int j = g; j < N && a.size() < 3; j += g) {
        if(!cnt[j]) continue;
        for(int t = 0; t < cnt[j] && a.size() < 3; t++) a.push_back(j);
      }
      if(a.size() == 3) {
        cout << a[0] << " " << a[1] << " " << a[2];
        return;
      }
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
