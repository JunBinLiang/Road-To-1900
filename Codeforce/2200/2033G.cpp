#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
  out << "]";
  return out;
}

const int INF = 1e7;
struct MaxSeg {
    struct Node {
        int l, r;
        int mx;
        int idx;
    } tr[(200000 + 100) * 4];

    void build(int id) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].idx = l;
            return;
        }
        int mid = l + (r - l) / 2;
        tr[id * 2 + 1] = {l, mid, -INF};
        tr[id * 2 + 2] = {mid + 1, r, -INF};
        build(id * 2 + 1);
        build(id * 2 + 2);
    }

    void update(int id, int index, int val) { 
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].mx = val;
            return;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
        }
        if(tr[left].mx > tr[right].mx) {
            tr[id].idx = tr[left].idx;
        } else {
            tr[id].idx = tr[right].idx;
        }
        tr[id].mx = max(tr[left].mx, tr[right].mx);
    }

    pair<int, int> query(int id, int s, int e) {
        int l = tr[id].l, r = tr[id].r;
        if(l == s && r == e){
            return {tr[id].mx, tr[id].idx};
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            pair<int, int> p1 = query(left, s, mid);
            pair<int, int> p2 = query(right, mid + 1, e);
            if(p1.first > p2.first) return p1;
            else return p2;
        }
    }
} maxseg;

const int N = 2e5 + 10;
vector<int> g[N];
vector<pair<int, int>> q[N];
vector<pair<int, int>> maxs[N];
int ans[N], height[N];

int dfs1(int pa, int u) {
    int h = 1;
    vector<pair<int, int>> b;
    for(int v : g[u]) {
        if(v == pa) continue;
        int subh = dfs1(u, v); //subtree height
        h = max(h, subh + 1);
        b.push_back({subh, v});
    }
    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());
    for(int i = 0; i < min(2, (int)(b.size())); i++) {
        maxs[u].push_back(b[i]);
    }

    height[u] = h;
    return h;
}

void dfs2(vector<int>& path, int pa, int u) {
    for(int i = 0; i < q[u].size(); i++) {
        pair<int, int>& p = q[u][i];
        int k = p.first, idx = p.second;
        ans[idx] = max(ans[idx], height[u] - 1);
        if(k == 0 || u == 1) continue;
        //up to k steps
        pair<int, int> best = maxseg.query(0, max(0, (int)(path.size() - k)), path.size() - 1);
        int j = best.second;
        ans[idx] = max(ans[idx], (int)(path[j] + (path.size() - j) - (2 * INF - j)));
    }


    auto& vec = maxs[u];
    for(int v : g[u]) {
        if(v == pa) continue;
        int pos = -1;
        for(int j = 0; j < vec.size(); j++) {
            if(vec[j].second != v) {
                pos = j;
                break;
            }
        }
        int sz = path.size();
        if(pos == -1) {
            path.push_back(0 + 2 * INF - (sz));
        } else{
            path.push_back((vec[pos].first) + 2 * INF - (sz));
        }

        maxseg.update(0, path.size() - 1, path.back());
        dfs2(path, u, v);
        maxseg.update(0, path.size() - 1, -INF);
        path.pop_back();
    } 
}

void solve() {
    int n, m;
    cin >> n;
    for(int i = 1; i <= n; i++) {
        g[i].clear();
        q[i].clear();
        maxs[i].clear();
    }
    
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    //move up: decrease
    //move down: no change
    cin >> m;
    for(int i = 0; i <= m; i++) ans[i] = 0;
    for(int i = 0; i < m; i++) {
        int u, k;
        cin >> u >> k;
        q[u].push_back({k, i});
    }

    dfs1(-1, 1);

    vector<int> path;
    maxseg.tr[0] = {0, n, -INF};
    maxseg.build(0);
    dfs2(path, -1, 1);

    for(int i = 0; i < m; i++) cout << ans[i] << " ";
    cout << endl;
}

int main(){
    int t = 1;
    ios::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
