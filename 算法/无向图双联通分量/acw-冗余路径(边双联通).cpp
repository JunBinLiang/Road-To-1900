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

/*
题意： 给一个无向连通图，最少加几条边可以把它变成边双联通分量

题解: 
    构造：缩点之后(是棵树)叶子的数量 + 1 的一半。连接每两个叶子节点
*/

const int N = 5010;
int e[N][N];
vector<int> g[N];
int dfn[N], low[N], ids[N];
int in[N];
vector<int> stk;
int t = 0, com = 0;
vector<pair<int, int>> bridges;
void tarjan(int pa, int u) {
    dfn[u] = low[u] = ++t;
    stk.push_back(u);
    for(int v : g[u]) {
        if(!dfn[v]) {
            tarjan(u, v);
            low[u] = min(low[u], low[v]);
            if(dfn[u] < low[v]) { //u v is bridge
                bridges.push_back({u, v});
            }
        } else if(v != pa) {
            low[u] = min(low[u], dfn[v]);
        } else if(v == pa && e[u][v] > 1) {
            //not from parent and make sure there is no duplicate edge, duplicate edges should be considered as the same component
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(dfn[u] == low[u]) { //不能走到上面
        com++;
        while(stk.size() > 0) {
            int top = stk.back();  
            stk.pop_back();
            ids[top] = com;
            if(top == u) break;
        }
    } 
}

void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        e[u][v]++;
        e[v][u]++;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(in, 0, sizeof in);
    t = 0;
    tarjan(-1, 1);
    
    for(auto p : bridges) {
        int u = p.first, v = p.second;
        in[ids[u]]++;
        in[ids[v]]++;
    }

    int cnt = 0;
    for(int i = 1; i <= com; i++) {
        if(in[i] == 1) {
            cnt++;
        }
    }
    cout << (cnt + 1) / 2 << endl;
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
