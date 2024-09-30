#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string.h>

using namespace std;  
using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define ve vector

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//1:15 - 1:55
const int MOD = 998244353;
const int N = 3e5 + 10;
int a[N];

long long get(vector<long long>& pdp, int l, int r) {
    if(l > r) return 0;
    return (pdp[r] - pdp[l - 1] + MOD) % MOD;
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }
    
    //last element index is i, current is j => min(a[i + 1], a[j - 1]) < min(a[i], a[j])

    /*vector<int> dp(n + 1);
    dp[0] = 1;
    for(int i = 1; i <= n; i++) {
        int culMin = 1000000000;
        for(int j = i - 1; j >= 0; j--) {
            int mn = a[i];
            if(j > 0) mn = min(mn, a[j]);
            if(mn < culMin) {
                dp[i] += dp[j];
            }
            culMin = min(culMin, a[j]);
        }
    }

    int ans = 0;
    int mn = 1000000000;
    for(int i = n; i >= 1; i--) {
        if(a[i] < mn) {
            ans += dp[i];
        }
        mn = min(mn, a[i]);
    }
    cout << ans << endl;*/

    vector<long long> dp(n + 1);
    vector<long long> pdp(n + 1);
    dp[0] = 1;
    pdp[0] = 1;
    vector<int> stk;
    long long s = 0;
    for(int i = 1; i <= n; i++) {
        while(stk.size() > 0 && a[i] < a[stk.back()]) {
            int j = stk.back(); stk.pop_back();
            s -= dp[j];
            if(s < 0) s += MOD;
        }

        if(stk.size() == 0) {
            dp[i] = pdp[i - 1];
            stk.push_back(i);
            s += dp[i];
            s %= MOD;
        } else {
            int j = stk.back();
            dp[i] += get(pdp, j + 1, i - 1);
            dp[i] %= MOD;
            dp[i] += s;
            dp[i] %= MOD;
            stk.push_back(i);
            s += dp[i];
            s %= MOD;
        }
        pdp[i] = (pdp[i - 1] + dp[i]) % MOD;
    }

    //cout << dp << endl;
    long long ans = 0;
    int mn = 1e9;
    for(int i = n; i >= 1; i--) {
        if(a[i] < mn) {
            ans += dp[i];
            ans %= MOD;
        }
        mn = min(mn, a[i]);
    }
    cout << ans << endl;
}

int main(){
  int t = 1;
  cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
