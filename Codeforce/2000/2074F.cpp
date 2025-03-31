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
    int L1, R1, L2, R2;
    cin >> L1 >> R1 >> L2 >> R2;
    long long ans = 0;
    while(L1 < R1) {
        int t = -1;
        for(int i = 21; i >= 0; i--) {
            if(((L1 % (1 << i) ) == 0) && L1 + (1 << i) <= R1) {
                t = i;
                break;
            }
        }
        int l = L2, r = R2;
        while(l < r) {
            for(int i = t; i >= 0; i--) {
                if((l % (1 << i) == 0) && l + (1 << i) <= r) {
                    if(i == t) {
                        int len = 1 << i;
                        int cnt = (r - l) / len;
                        l += ((1 << i) * cnt);
                        ans += (cnt);
                    } else {
                        ans += ((1 << t) / (1 << i));
                        l += (1 << i);
                    }
                    break;
                }
            }
        }
        L1 += (1 << t);
    }
    cout << ans << endl;
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
