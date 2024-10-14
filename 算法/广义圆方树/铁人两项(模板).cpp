//https://vjudge.net/problem/%E6%B4%9B%E8%B0%B7-P4630
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
#include <random>
#include <chrono>

using namespace std;  
using ll = long long;
using ull = unsigned long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int N =  2e5 + 100, INF = 1e8;
struct E {
    int v, w, ei;
};
vector<E> g1[N], g2[N];
int dfn[N], low[N], cut[N];
vector<int> stk;
int t = 0, ei = 0;
int newnode;
long long ans = 0;
int treesz = 0;
int n, m;

void add(vector<E> g[N], int u, int v, int w) {
    g[u].push_back({v, w, ei++});
    g[v].push_back({u, w, ei++});
}

void add1(vector<E> g[N], int u, int v, int w) { //1 direction
    g[u].push_back({v, w, ei++});
}


void tarjan(int root, int u) {
    treesz++;
    dfn[u] = low[u] = ++t;
    stk.push_back(u);
    
    int cnt = 0;
    for(auto& e : g1[u]) {
        int v = e.v;
        if(!dfn[v]) {
            tarjan(root, v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] <= low[v]) { //v 搜不到u 上面，所以u可能是割点
                cnt++;
                if(u != root || cnt > 1) { //cut point
                    cut[u] = true;
                }
                int x;
                newnode++;
                do {
                    x = stk.back();
                    stk.pop_back();
                    add(g2, newnode, x, 1);
                    //cout << "add " << newnode << " " << x << endl;
                } while (x != v);
                add(g2, newnode, u, 1);
                //cout << "add " << newnode << " " << u << endl << endl;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int sz[N];
void dfs(int pa, int u) {
    sz[u] = 0;
    if(u <= n) sz[u] = 1;
    
    long long val = -1;
    if(u > n) val = g2[u].size();

    int cnt = 0, cen = 0;
    long long s = 0;
    for(auto& e : g2[u]) {
        if(e.v == pa) continue;
        dfs(u, e.v);
        sz[u] += sz[e.v];

        if(u <= n) {
            s += (val * cnt * sz[e.v]);
            cnt += sz[e.v];
        } else {
            //center to center is calculated below, skip
            //noncenter to center
            s += ((val - 1) * (cnt - cen) * 1);
            //center to noncenter
            s += ((val - 1) * cen * (sz[e.v] - 1));
            //noncenter to noncenter
            s += (val * (cnt - cen) * (sz[e.v] - 1));
            cnt += sz[e.v];
            cen++;
        }
    }
    //cout << "gg " << u << " " << s << endl;
    if(u <= n) {
        s += (val * (sz[u] - 1) * (treesz - sz[u]));
    } else {
        int center = g2[u].size();
        int noncenterdown = sz[u] - cen;
        int other = treesz - center - noncenterdown;
        //noncenter to other
        s += (val * noncenterdown * other);
        //noncenter to up center
        s += ((val - 1) * noncenterdown * 1);
        
        //center to other
        s += ((val - 1) * (cen) * other);
        //center to center
        if(val >= 2) {
            s += ((val - 2) * ((center + 0ll) * (center - 1) / 2));
        } 

    }
    ans += s;
    //cout << "gg " << u << " " << s << endl << endl;
}

/*
题意：给无向图，找有多少个triple s, c, f， 使得路劲s -> c -> f，每个点只能被访问一次

假设枚举s f, c一定在s -> f 路劲上所有的方点的点联通分量上
*/
void solve() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        add(g1, u, v, 1);
    }

    memset(dfn, 0, sizeof dfn);
    memset(low, 0, sizeof low);
    memset(cut, 0, sizeof cut);
    newnode = n + 5;
    
    
    for(int i = 1; i <= n; i++) {
        if(!dfn[i]) {
            stk.clear();
            t = 0;
            treesz = 0;
            tarjan(i, i);
            dfs(-1, i);
        }
    }
    cout << ans * 2 << endl;
}

int main(){
    int t = 1;
    //cin >> t;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    while(t--) {
        solve();
    }
    return 0;
}
