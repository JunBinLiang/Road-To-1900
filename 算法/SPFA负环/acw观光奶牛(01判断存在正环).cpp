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
const int N = 1010;
vector<pair<int, int>> g[N];

bool spfa(int n, vector<int>& a, double mid) {
    vector<double> dist(n + 1);
    vector<int> cnt(n + 1);
    vector<bool> vis(n + 1);
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        dist[i] = 0;
        vis[i] = true;
        q.push(i);
    }

    while(q.size()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for(auto& p : g[u]) {
            int v = p.first, c = p.second;
            double w = a[u] - mid * c;
            if(dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return true;
                if(!vis[v]) {
                    vis[v] = true;
                    q.push(v);
                }

            }
        }
    }
    return false;
}

/*
给定一张 L个点、P条边的有向图，每个点都有一个权值 f[i]
，每条边都有一个权值 t[i]

求图中的一个环，使“环上各点的权值之和” 除以 “环上各边的权值之和” 最大。
输出这个最大值。
*/

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }
    
    double l = 0, r = 1e6;
    while (r - l > 1e-4)
    {
        double mid = (l + r) / 2;
        if (spfa(n, a, mid)) l = mid;
        else r = mid;
    }
    printf("%.2lf\n", l);
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
