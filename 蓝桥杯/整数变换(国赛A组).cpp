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

const int N = 1e5 + 10;
const int MOD = 1e9 + 7, BASE = 101;
unsigned long long p[N];

int get(int n) {
    int ans = 0;
    while(n) {
        ans += (n % 10);
        n /= 10;
    }
    return ans;
}


void solve() {
    int n;
    cin >> n;
    int ans = 0;
    while(n) {
        n -= get(n);
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
