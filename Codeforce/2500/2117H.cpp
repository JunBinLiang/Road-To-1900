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


const int N = 3e5 + 100;

struct Node {
    int l, r;
    int ls, rs, s, ans;
} tr[N * 4];

void pushup(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[u].s = tr[left].s + tr[right].s;
    tr[u].ls = max(max(tr[left].ls, tr[left].s + tr[right].ls), 0);
    tr[u].rs = max(max(tr[right].rs, tr[left].rs + tr[right].s), 0);
    tr[u].ans = max(tr[left].ans, tr[right].ans);
    tr[u].ans = max(tr[u].ans, tr[left].rs + tr[right].ls);
}

void build(int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].ls = tr[u].rs = 0;
        tr[u].s = -1;
        tr[u].ans = 0;
        return;
    }
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid, 0, 0, 0, 0};
    tr[u * 2 + 2] = {mid + 1, r, 0, 0, 0, 0};
    build(u * 2 + 1);
    build(u * 2 + 2);
    pushup(u);
}

void update(int u, int index, int val) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        tr[u].s = val;
        tr[u].ls = tr[u].rs = max(0, val);
        tr[u].ans = max(0, val);
        return;
    }
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, val);
    } else {
        update(u * 2 + 2, index, val);
    }
    pushup(u);
}

struct T {
    int i, t, op;
};
vector<T> q[N];

void del(map<int, int>& mp, int k) {
    mp[k]--;
    if(mp[k] == 0) {
        mp.erase(k);
    }
}

vector<pair<int, int>> upd[N];

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for(int i = 0; i <= m + 1; i++) upd[i].clear();
    for(int i = 0; i <= n; i++) q[i].clear();
    for(int i = 1; i <= n; i++) {
        q[a[i]].push_back({i, 0, 1});
    }

    for(int i = 1; i <= m; i++) {
        int j, x;
        cin >> j >> x;
        int old = a[j];
        if(old == x) continue;
        q[old].push_back({j, i, -1});
        a[j] = x;
        q[x].push_back({j, i, 1});
    }

    tr[0] = {1, n, 0, 0, 0, 0};
    build(0);
    
    
    for(int i = 1; i <= n; i++) {
        int pt = -1, pans = -1;
        for(auto& p : q[i]) {
            int index = p.i, t = p.t, op = p.op;
            update(0, index, op);
            int ans = tr[0].ans;
            upd[t].push_back({ans, 1});
            if(pt != -1) {
                upd[t].push_back({pans, -1});
            }
            pans = ans;
            pt = t;
        }

        //finish all update, reset to all -1
        for(auto& p : q[i]) {
            int index = p.i;
            update(0, index, -1);
        }
    }

    map<int, int> mp;
    for(int t = 0; t <= m; t++) {
        for(auto& p : upd[t]) {
            int ans = p.first;
            int op = p.second;
            if(op == 1) {
                mp[ans]++;
            } else {
                del(mp, ans);
            }
        }
        if(t > 0) {
            auto it = mp.end();
            it--;
            cout << it -> first / 2 << " ";
        }
    }
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
