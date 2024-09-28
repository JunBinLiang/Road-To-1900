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

//11:48 - 12:48
const int N = 1e5 + 10;
vector<pair<int, int>> g[N];

void output(vector<int> & a) {
    for(int i = 1; i < a.size(); i++) printf("%d ", a[i]);
    printf("\n");
}

void dfs(vector<int>& vis, vector<int>& com, int u) {
    vis[u] = true;
    com.push_back(u);
    for(pair<int, int>& p : g[u]) {
        int v = p.first;
        if(vis[v]) continue;
        dfs(vis, com, v);
    }
}

void dfs1(vector<int>& vec, int u, int ith, int bit) {
    if(vec[u] != -1) return;
    vec[u] = bit;
    //cout << "dfs1  " << u << " " << bit << endl;
    for(pair<int, int>& p : g[u]) {
        int v = p.first, x = p.second;
        if(vec[v] != -1) continue;
        int b = 0;
        if(x & (1 << ith)) b = 1;
        if(bit == 0) {
            dfs1(vec, v, ith, b);
        } else { //no dfs
        }
    }
}

void dfs2(vector<int>& vec, int u, int ith ,int bit) {
    if(vec[u] != -1) return;
    vec[u] = bit;
    //cout << "dfs2  " << u << " " << bit << "  " << vec << endl;
    for(pair<int, int>& p : g[u]) {
        int v = p.first, x = p.second;
        if(vec[v] != -1) continue;
        if(bit == 0) {
            dfs2(vec, v, ith, 1);
        } else {    
            
        }
    }
}

void solve() {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        if(u > v) swap(u, v);
        g[u].push_back({v, x});
        g[v].push_back({u, x});
    }

    vector<int> ans(n + 1);
    for(int i = 0; i < 31; i++) {
        //if(i == 0) continue;
        vector<int> vis(n + 1);
        vector<int> vec(n + 1, -1); //vals
        for(int u = 1; u <= n; u++) {
            if(vis[u]) continue;
            vector<int> com;
            dfs(vis, com, u);
            sort(com.begin(), com.end());
            //cout << "component  " << com << endl;
            for(int node : com) {
                for(pair<int, int>& p : g[node]) {
                    if(node == p.first) {
                        if(p.second & (1 << i)) vec[node] = 1;
                        else {
                          //vec[node] = 0;
                          dfs1(vec, node, i, 0);
                          //cout << node << endl;
                        }
                    }
                }
            }

            for(int node : com) {
                for(pair<int, int>& p : g[node]) {
                    if((p.second & (1 << i)) == 0) { //zero node
                        dfs1(vec, node, i, 0);
                    }
                }
            }
            //cout << vec << endl;
            for(int node : com) {
                if(vec[node] != -1) continue;
                dfs2(vec, node, i, 0);
            }
        }
        //cout << "before ans  " << ans << endl;
        for(int j = 1; j <= n; j++) {
            ans[j] += (vec[j] << i);
        }
        //cout << "after ans  " << ans << endl;
        //break;
    }
    output(ans);
}

int main(){
  int t = 1;
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
