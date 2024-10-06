#include <bits/stdc++.h>
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
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

const int MOD = 1e9 + 7;
const int MASK = (1 << 20) - 1;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    vector<long long> p(n + 1);
    p[0] = 1;
    for(int i = 1; i < p.size(); i++) {
        p[i] = p[i - 1] * 2; 
        p[i] %= MOD;
    }

    //Find a sequence with and = 0 => 反转每个数的bit，那他的or 就得全是1
    vector<long long> dp((1 << 20) + 10);
    for(int i = 0; i < n; i++) {
        dp[MASK - a[i]]++;
    }

    //Find how many sequence that or = 111....111

    for(int i = 0; i < 20; i++) {
        for(int st = (1 << 20) - 1; st >= 0; st--) {
            if(st & (1 << i)) {
                dp[st] += dp[st ^ (1 << i)];
            }
        }
    }

    for(int i = 0; i < dp.size(); i++) {
        dp[i] = p[(int)(dp[i])] - 1;
    }

    //容斥
    for(int i = 0; i < 20; i++) {
        for(int st = (1 << 20) - 1; st >= 0; st--) {
            if(st & (1 << i)) {
                dp[st] -= dp[st ^ (1 << i)];
                if(dp[st] < 0) dp[st] += MOD;
            }
        }
    }

    cout << dp[MASK] << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    //cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
