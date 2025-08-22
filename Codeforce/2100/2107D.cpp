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
vector<int> g[N];
int fa[N];
bool vis[N];
map<int, pair<int, int>> mps[N];
set<pair<int, int>> sets[N];

struct Path {
    int r, d, from, to;
    void init() {
        if(from < to) swap(from, to);
    }
} cur[N];

struct Comp {
    bool operator()(const Path& p1, const Path& p2) { //maxheap
        if(p1.d == p2.d) {
            if(p1.from == p2.from) {
                return p1.to < p2.to;
            }
            return p1.from < p2.from;
        }
        return p1.d < p2.d;
    }
};
priority_queue<Path, vector<Path>, Comp> pq;

pair<int, int> dfs1(int pa, int u) {
    fa[u] = pa;
    vector<pair<int, int>> a;
    for(int v : g[u]) {
        if(pa == v) continue;
        auto p = dfs1(u, v);
        a.push_back(p);
        mps[u][v] = p;
        sets[u].insert(p);
    }
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    if(a.size() == 0) {
        int len = 1;
        Path p = {u, len, u, u};
        p.init();
        cur[u] = p;
        pq.push(p);
        return {1, u};
    } else if(a.size() == 1) {
        int len = a[0].first + 1;
        Path p = {u, len, u, a[0].second};
        p.init();
        cur[u] = p;
        pq.push(p);
        return {1 + a[0].first, a[0].second};
    } else {
        int len = a[0].first + 1 + a[1].first;
        Path p = {u, len, a[0].second, a[1].second};
        p.init();
        cur[u] = p;
        pq.push(p);
        return {1 + a[0].first, a[0].second};
    }
}

void update(int u, int v, int bottom, int len, pair<int, int> best) {
    set<pair<int, int>>& s = sets[u];
    pair<int, int> p = mps[u][v];
    s.erase(p);
    mps[u].erase(v);


    if(len > 0) {
        mps[u][v] = best;
        s.insert(best);
    }

    if(s.size() == 0) {
        Path p = {u, 1, u, u};
        p.init();
        cur[u] = p;
        pq.push(p);
    } else if(s.size() == 1) {
        auto it1 = s.end(); it1--;
        Path p = {u, 1 + it1 -> first, u, it1 -> second};
        p.init();
        cur[u] = p;
        pq.push(p);
    } else {
        auto it1 = s.end(); it1--;
        auto it2 = s.end(); it2--; it2--;
        Path p = {u, 1 + it1 -> first + it2 -> first, it1 -> second, it2 -> second};
        p.init();
        cur[u] = p;
        pq.push(p);
    }
    //cout << "after update :" << u << "  |" << cur[u].r << " " << cur[u].from << " " << cur[u].to << " " << cur[u].d << endl;
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        fa[i] = -1;
        vis[i] = false;
        mps[i].clear();
        sets[i].clear();
    }

    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs1(-1, 1);

    vector<int> ans;
    while(pq.size() > 0) {
        auto p = pq.top(); pq.pop();
        int u = p.r, d = p.d, from = p.from, to = p.to;
        if(vis[u]) continue;
        if(d != cur[u].d || from != cur[u].from || to != cur[u].to) {
            continue;
        }
        
        //cout << from << "  " << to << " " << u << endl;
        ans.push_back(d);
        ans.push_back(from);
        ans.push_back(to);
        while(from != u) {
            vis[from] = true;
            from = fa[from];
        }
        while(to != u) {
            vis[to] = true;
            to = fa[to];
        }
        vis[u] = true;
        
        int prev = u;
        u = fa[u];
        int bottom = u;
        int len = 0;
        while(u != -1 && !vis[u]) {
            if(len == 0) {
                update(u, prev, bottom, len, {0, 0});
            } else {
                set<pair<int, int>>& s = sets[prev];
                if(s.size() == 0) {
                    update(u, prev, bottom, len, {1, prev});
                } else {
                    auto it = s.end(); it--;
                    update(u, prev, bottom, len, {1 + it -> first, it -> second});
                }
            }
            prev = u;
            u = fa[u];
            len++;
        }
    }
    for(int x : ans) cout << x << " ";
    cout << endl;
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
