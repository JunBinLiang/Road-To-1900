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

const int MAX = 2e5 + 50, INF = 1e9;
struct MaxSeg {
    struct Node {
        int l, r;
        int mx;
    } tr[MAX * 4];

    void build(int id) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
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
            tr[id].mx = max(tr[id].mx, val);  
            return;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
        }
        tr[id].mx = max(tr[left].mx, tr[right].mx);
    }

    int query(int id, int s, int e) {
        int l = tr[id].l, r = tr[id].r;
        if(l == s && r == e){
            return tr[id].mx;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return max(query(left, s, mid), query(right, mid + 1, e));
        }
    }
} tr1, tr2;

const int N = 2e5 + 10;
int U, V;
vector<int> g[N], a;
bool is[N];
int d[N];

void dfs(vector<int>& path, int pa, int u) {
    path.push_back(u);
    if(u == U) {
        a = vector<int>(path.begin(), path.end());
    }
    for(int v : g[u]) {
        if(pa == v) continue;
        dfs(path, u, v);
    }
    path.pop_back();
}

int dfs1(int pa, int u) {
    int h = 1;
    for(int v : g[u]) {
        if(v == pa) continue;
        int l = dfs1(u, v);
        if(!is[v]) {
            h = max(h, 1 + l);
        }
    }
    d[u] = h;
    return h;
}

void solve() {
    int n;
    cin >> n;
    for(int i = 0; i <= n; i++) {
        g[i].clear();
        is[i] = false;
    }
    for(int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cin >> U >> V; //U == V
    vector<int> path;
    dfs(path, -1, 1);
    for(int u : a) is[u] = true;
    dfs1(-1, 1);

    tr1.tr[0] = {0, a.size() - 1, -INF};
    tr1.build(0);
    tr2.tr[0] = {0, a.size() - 1, -INF};
    tr2.build(0);
    
    //for(int x : a) cout << x << " ";
    //cout << endl;
    
    for(int i = 0; i < a.size(); i++) {
        //Alice Move
        int u = a[i];
        tr1.update(0, i, i + d[u]);
        //Bob Move
        tr2.update(0, i, d[u] + (a.size() - i - 1));
    }

    int l = 0, r = a.size() - 1;    
    for(int i = 0; i < a.size() && l < r; i++) {
        if(i % 2 == 0) { //alice
            int bmax = tr2.query(0, l + 1, r);
            int amax = l + d[a[l]];
            //cout << i << " " << l << " " << a[l] << "   |" << amax << " " << bmax << endl;
            if(amax > bmax) {
                cout << "Alice" << endl;
                break;
            }
            l++;
            if(l == r) { //can not move anymore
                cout << "Bob" << endl;
                break;
            } 
        } else { //Bob
            int amax = tr1.query(0, l, r - 1);
            int bmax = d[a[r]] + (a.size() - r - 1);
            //cout << i << " " << r << " " << a[r] << "   |" << amax << " " << bmax << endl;
            if(bmax >= amax) {
                cout << "Bob" << endl;
                break;
            }
            r--;
            if(l == r) { //can not move anymore
                cout << "Alice" << endl;
                break;
            } 
        }
    }
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
