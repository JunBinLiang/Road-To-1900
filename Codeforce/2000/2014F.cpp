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
#include <deque>

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
ostream &operator<<(ostream &out, const set<T> &a) {
  out << "[";
  bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;}
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//3:49 - 3:59
const int N = 2e5 + 10;
const long long INF = 10000000000000000ll;
vector<int> g[N];
int a[N];
long long dp[N][2]; // two states
int n, k;
void dfs(int pa, int u) {
    dp[u][0] = 0; //no action
    dp[u][1] = a[u]; //strength

    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        if(dp[v][0] > dp[v][1] - 2 * k) { 
            dp[u][1] += dp[v][0];
        } else {
            dp[u][1] += (dp[v][1] - 2 * k);
        }
    }
}

void solve() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for(int i = 0; i <= n; i++) g[i].clear();

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i = 0; i <= n; i++) {
        dp[i][0] = dp[i][1] = -INF;
    }

    dfs(-1, 1);
    long long ans = max(dp[1][0], dp[1][1]);
    ans = max(0ll, ans);
    cout << ans << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
