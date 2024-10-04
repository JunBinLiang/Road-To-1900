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

//3:36 - 4:16
const int N = 2e5 + 10;
vector<int> g[N];
int a[N];
long long ans = 0;
unordered_map<int, int> mps[N];

void dfs(int pa, int u) {
    int c = a[u];
    for(int v : g[u]) {
        if(v == pa) continue;
        dfs(u, v);
        if(mps[v].size() > mps[u].size()) {
            swap(mps[v], mps[u]);
        }
        
        for(auto it = mps[v].begin(); it != mps[v].end(); it++) {
            int color = it -> first, cnt = it -> second;
            if(color == c) {
                
            } else {
                ans += ((cnt + 0ll) * mps[u][color]);
            }
            mps[u][color] += cnt;
        }
    }
    ans += mps[u][c];
    mps[u][c] = 1;
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) g[i].clear();
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    ans = 0;
    for(int i = 0; i <= n; i++) mps[i].clear();
    dfs(-1, 1);
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
