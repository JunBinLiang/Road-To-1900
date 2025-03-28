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

const int N = 1e5 + 10;

struct PST {
    struct Node {
        int l, r, s, lu, ru;
    } tr[N * 40];
    int id = 0;
    int roots[N * 2];

    int newnode(int l, int r, int s) {
        int u = ++id;
        tr[u] = {l, r, s};
        return u;
    }

    void init(int n) {
        int u = newnode(0, n, 0);
        roots[0] = u;
        build(u);
    }

    void build(int u) {
        int l = tr[u].l, r = tr[u].r;
        if(l == r) {
            return;
        }
        int mid = l + (r - l) / 2;
        tr[u].lu = newnode(l, mid, 0); tr[u].ru = newnode(mid + 1, r, 0);
        build(tr[u].lu);
        build(tr[u].ru);
    }

    void pushup(int u) {
        if(tr[u].l != tr[u].r) {
            int lu = tr[u].lu, ru = tr[u].ru;
            tr[u].s = tr[lu].s + tr[ru].s;
        }
    }

    void update(int pu, int u, int index, int val) {
        int l = tr[u].l, r = tr[u].r;
        if(l == r) {
            tr[u].s += val;
            return;
        }

        int mid = l + (r - l) / 2;
        if(index <= mid) { //update left
            tr[u].ru = tr[pu].ru;
            int lu = newnode(l, mid, tr[tr[pu].lu].s);
            tr[u].lu = lu;
            update(tr[pu].lu, tr[u].lu, index, val);
        } else {
            int ru = newnode(mid + 1, r, tr[tr[pu].ru].s);
            tr[u].lu = tr[pu].lu;
            tr[u].ru = ru;
            update(tr[pu].ru, tr[u].ru, index, val);
        }
        pushup(u);
    }

    int query(int u, int s, int e) {
        int l = tr[u].l, r = tr[u].r;
        if(l == s && r == e) {
            return tr[u].s;
        }
        int mid = l + (r - l) / 2;
        int lu = tr[u].lu, ru = tr[u].ru;
        if(e <= mid) {
            return query(lu, s, e);
        } else if(s >= mid + 1) {
            return query(ru, s, e);
        } else {
            return query(lu, s, mid) + query(ru, mid + 1, e);
        }
    }
} pst;



int a[N];
void solve() {
    int n, m;
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    pst.init(n);

    unordered_map<int, int> mp;
    for(int i = 1; i <= n; i++) {
        int p1 = i * 2 - 1, p2 = i * 2;
        int u1 = pst.newnode(0, n, 0);
        int u2 = pst.newnode(0, n, 0);
        pst.roots[p1] = u1;
        pst.roots[p2] = u2;
        pst.update(pst.roots[p1 - 1], u1, i, 1);
        if(mp.find(a[i]) != mp.end()) {
            int last = mp[a[i]];
            pst.update(u1, u2, last, -1);
        } else {
            pst.update(u1, u2, i, 0);
        }
        mp[a[i]] = i;
    }

    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        int s = pst.query(pst.roots[r * 2], l, r);
        cout << s << endl;
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
