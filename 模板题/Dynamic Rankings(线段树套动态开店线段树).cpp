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

const int N = 2e5 + 100;
int a[N];
int n, m;

//动态开点线段树
struct T {
    int s;
    int lu = -1, ru = -1;
} segt[N * 130];
int id = 0;
int newnode(int s) {
    int u = ++id;
    segt[u] = {s};
    return u;
}
void pushup(int u) {
    segt[u].s = 0;
    int lu = segt[u].lu, ru = segt[u].ru;
    if(lu != -1) segt[u].s += segt[lu].s;
    if(ru != -1) segt[u].s += segt[ru].s;
}

void add(int u, int l, int r, int index, int val) {
    if(l == r) {
        segt[u].s += val;
        return;
    }

    int mid = l + (r - l) / 2;
    if(index <= mid) {
        if(segt[u].lu == -1) {
            segt[u].lu = newnode(0);
        }
        add(segt[u].lu, l, mid, index, val);
    } else {
        if(segt[u].ru == -1) {
            segt[u].ru = newnode(0);
        }
        add(segt[u].ru, mid + 1, r, index, val);
    }
    pushup(u);
}

int qu(int u, int l, int r, int s, int e) {
    if(u == -1) return 0;
    if(l == s && r == e) {
        return segt[u].s;
    }
    int mid = l + (r - l) / 2;
    if(e <= mid) return qu(segt[u].lu, l, mid, s, e);
    else if(s >= mid + 1) return qu(segt[u].ru, mid + 1, r, s, e);
    else {
        return qu(segt[u].lu, l, mid, s, mid) + qu(segt[u].ru, mid + 1, r, mid + 1, e);
    }
}




//权值线段树
struct Node {
    int l, r;
    int root = -1;
    void init() {
        root = newnode(0);
    }
} tr[4 * N];

void build(int u) {
    tr[u].init();
    if(tr[u].l == tr[u].r) {
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    tr[left] = {l, mid};
    tr[right] = {mid + 1, r};
    build(left);
    build(right);
}

void update(int u, int arrIndex, int index, int val) {
    int l = tr[u].l, r = tr[u].r;
    add(tr[u].root, 1, n, arrIndex, val);
    if(l == r) {
        return;
    }
    int mid = l + (r - l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, arrIndex, index, val);
    } else {
        update(u * 2 + 2, arrIndex, index, val);
    }
}

//query the k
int dfs(int u, int L, int R, int k) {
    if(tr[u].l == tr[u].r) {
        return tr[u].l;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    int cnt = qu(tr[left].root, 1, n, L, R);
    if(k <= cnt) {
        return dfs(left, L, R, k);
    } else {
        return dfs(right, L, R, k - cnt);
    }
}


struct Q {
    int op;
    int pos, val, l, r, k;
} q[N];


void solve() {
    cin >> n >> m;
    vector<int> b;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        b.push_back(a[i]);
    }

    for(int i = 0; i < m; i++) {
        char c;
        cin >> c;
        int op; //cin >> op;
        if(c == 'Q') op = 2;
        else op = 1;
        if(op == 1) {
            int pos, val;
            cin >> pos >> val;
            b.push_back(val);
            q[i].op = op;
            q[i].pos = pos;
            q[i].val = val;
        } else {
            q[i].op = op;
            cin >> q[i].l >> q[i].r >> q[i].k;
        }
    }

    sort(b.begin(), b.end());
    unordered_map<int, int> mp1, mp2;
    int id = 0;
    for(int i = 0; i < b.size(); i++) {
        if(mp1.find(b[i]) == mp1.end()) {
            mp1[b[i]] = id;
            mp2[id] = b[i];
            id++;
        }
    }

    tr[0] = {0, id + 2};
    build(0);
    for(int i = 1; i <= n; i++) {
        int v = mp1[a[i]];
        update(0, i, v, 1);
    }
    
    for(int i = 0; i < m; i++) {
        int op = q[i].op;
        if(op == 1) {
            int pos = q[i].pos, val = q[i].val;
            int old = a[pos];
            a[pos] = val;
            update(0, pos, mp1[old], -1); //delete the old one
            update(0, pos, mp1[val], 1); //add the new one
        } else {
            int l = q[i].l, r = q[i].r, k = q[i].k;
            int ans = dfs(0, l, r, k);
            cout << mp2[ans] << endl;
        }
    }
    
}


int main() {
  int t = 1;
  ios::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  //cin >> t;
  while(t--) {
    solve();
  }
  return 0;
}
