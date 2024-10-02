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
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

//1:58
const int N = 5e5 + 10;
set<int> g[N];
int p[N];
vector<pair<int, int>> a;

bool isleaf(int u) {
    return u != 1 && g[u].size() == 1;
}

void dfs(int pa, int u, int dep) {
    //cout << "dfs " << u << endl;
    p[u] = pa;
    a.push_back({dep, u});
    for(auto v : g[u]) {
        if(v == pa) continue;
        dfs(u, v, dep + 1);
    }
}

void solve() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        p[i] = -1;
    }
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].insert(v);
        g[v].insert(u);
    }
    
    a.clear();
    dfs(-1, 1, 0);

    int cnt = 0;
    int ans = 1e9;
    sort(a.begin(), a.end());

    for(int i = 0; i < a.size(); i++) {
        int j = i;
        vector<int> b;
        while(j < a.size() && a[i].first == a[j].first) {
            b.push_back(a[j].second);
            j++;
        }
        ans = min(ans, cnt + (n - j)); //delete all nodes have a higher height
        for(int u : b) {
            while(isleaf(u)) {
                g[p[u]].erase(u);
                u = p[u];
                cnt++;
            }
        }
        i = j - 1;
    }
    printf("%d\n", ans);
}

int main(){
    //ios::sync_with_stdio(false);
    //cin.tie(nullptr), cout.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
