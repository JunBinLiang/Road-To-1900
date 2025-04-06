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

const int N = 2e5 + 10;
int a[N], b[N], c[N], d[N];
int n; long long k;

long long cal(int k) {
    k--;
    for(int i = 0; i < n; i++) {
        c[i] = a[i];
        d[i] = b[i];
    }
    
    for(int i = 0; i < n; i++) {
        int t = min(c[i], d[i]);
        c[i] -= t;
        d[i] -= t;
    }

    //for(int i = 0; i < n; i++) cout << c[i] << " ";
    //cout << endl;
    //for(int i = 0; i < n; i++) cout << d[i] << " ";
    //cout << endl;

    int ans = 0;
    vector<int> stk;
    for(int i = 0; i < n; i++) {
        if(c[i] == 0 && d[i] == 0) continue;
        if(c[i]) {
            stk.push_back(i);
        } else if(d[i]) {
            while(stk.size() && d[i] && i - stk.back() <= k) {
                int j = stk.back();
                if(d[i] >= c[j]) {
                    stk.pop_back();
                    d[i] -= c[j];
                    c[j] = 0;
                } else {
                    c[stk.back()] -= d[i];
                    d[i] = 0;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        if(d[i]) {
            while(stk.size() && d[i] && (i + n - stk.back()) <= k) {
                int j = stk.back();
                if(d[i] >= c[j]) {
                    stk.pop_back();
                    d[i] -= c[j];
                    c[j] = 0;
                } else {
                    c[stk.back()] -= d[i];
                    d[i] = 0;
                }
            }
        }
    }

    long long need = 0;
    while(stk.size()) {
        int j = stk.back(); stk.pop_back();
        need += c[j];
    }

    return need;
}

void solve() {
    cin >> n >> k;
    long long s = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        s += a[i];
    }
    for(int i = 0; i < n; i++) cin >> b[i];

    if(k >= s) {
        cout << 0 << endl;
        return;
    }
    

    int ans = -1;
    int l = 1, r = n;
    while(l <= r) {
        int mid = l + (r - l) / 2;
        if(cal(mid) <= k) {
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
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
