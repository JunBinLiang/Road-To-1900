#include <iostream>
#include <cstring>
#include <algorithm>
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

const int N = 2e6 + 10, INF = 1e9;

struct Node {
    int l, r;  
    int flag, s, mn, mnIdx, mx, mxIdx;  
    void print() {
        cout << "Node " << l << " " << r << "  |" << s << "  " << mn << " " << mnIdx << "  " << mx << "  " << mxIdx << "  " << endl;
    }
} tr[N * 4];

void pushdown(int u) {
    if(tr[u].flag == 0) return;
    tr[u].flag ^= 1;
    if(tr[u].l == tr[u].r) {
        tr[u].s = -tr[u].s;
        tr[u].mn = tr[u].mx = tr[u].s;
        return;
    }
    int l = tr[u].l, r = tr[u].r;
    int left = u * 2 + 1, right = u * 2 + 2;
    int sz = tr[u].r - tr[u].l + 1;
    //positive + negative = sz
    //sum = positive - negative
    int positive = (sz + tr[u].s) / 2;
    int negative = sz - positive;
    tr[u].s = negative - positive;
    tr[left].flag ^= 1;
    tr[right].flag ^= 1;
    int oldmn = tr[u].mn, oldmx = tr[u].mx;
    tr[u].mn = -oldmx;
    tr[u].mx = -oldmn;
    if(tr)
    swap(tr[u].mnIdx, tr[u].mxIdx);

}

void pushup(int u) {
    if(tr[u].l == tr[u].r) {
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    pushdown(left);
    pushdown(right);
    tr[u].s = tr[left].s + tr[right].s;
    int lmn = tr[left].mn, rmn = tr[right].mn + tr[left].s;
    int lmx = tr[left].mx, rmx = tr[right].mx + tr[left].s;
    if(lmn < rmn) {
        tr[u].mn = lmn;
        tr[u].mnIdx = tr[left].mnIdx;
    } else {
        tr[u].mn = rmn;
        tr[u].mnIdx = tr[right].mnIdx;
    }
    if(lmx > rmx) {
        tr[u].mx = lmx;
        tr[u].mxIdx = tr[left].mxIdx;
    } else {
        tr[u].mx = rmx;
        tr[u].mxIdx = tr[right].mxIdx;
    }
}



void build(string& s, int u) {
    int l = tr[u].l, r = tr[u].r;
    if(l == r) {
        int val = 0;
        if(s[l - 1] == '(') {
            val = 1;
        } else {
            val = -1;
        }
        tr[u].s = val;
        tr[u].mn = val;
        tr[u].mnIdx = l;
        tr[u].mx = val;
        tr[u].mxIdx = l;
        return;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    int mid = l + (r - l) / 2;
    tr[left] = {l, mid, 0, 0, INF, -1, -INF, -1};
    tr[right] = {mid + 1, r, 0, 0, INF, -1, -INF, -1};
    build(s, left);
    build(s, right);
    pushup(u);
}

void update(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        tr[u].flag ^= 1;
        if(l == r) {
            pushdown(u);
        }
        return;
    }
    pushdown(u);
    int mid = l + (r - l) / 2;
    int left = u * 2 + 1, right = u * 2 + 2;
    if(e <= mid) {
        update(left, s, e);
    } else if(s >= mid + 1) {
        update(right, s, e);
    } else {
        update(left, s, mid);
        update(right, mid + 1, e);
    }
    pushup(u);
}

struct Q {
    int s, mn, mx, mnIdx, mxIdx, u;
    void print() {
        cout << "Q " << s << "   |" << mn << " " << mnIdx << "  " << mx << "  " << mxIdx << "  " << u << endl;
    }
};

Q merge(Q& q1, Q& q2) {
    Q q;
    q.s = q1.s + q2.s;
    int lmn = q1.mn, rmn = q2.mn + q1.s;
    int lmx = q1.mx, rmx = q2.mx + q1.s;
    if(lmn < rmn) {
        q.mn = lmn;
        q.mnIdx = q1.mnIdx;
    } else {
        q.mn = rmn;
        q.mnIdx = q2.mnIdx;
    }
    if(lmx > rmx) {
        q.mx = lmx;
        q.mxIdx = q1.mxIdx;
    } else {
        q.mx = rmx;
        q.mxIdx = q2.mxIdx;
    }

    q1.s = q.s;
    q1.mn = q.mn;
    q1.mx = q.mx;
    q1.mnIdx = q.mnIdx;
    q1.mxIdx = q.mxIdx;
    return q;
}

bool stop = false;
void dfs(Q& q, int u) {
    pushdown(u);
    int left = u * 2 + 1, right = u * 2 + 2;
    if(q.s + tr[u].mn >= 0) {
        Q q2 = {tr[u].s, tr[u].mn, tr[u].mx, tr[u].mnIdx, tr[u].mxIdx};
        merge(q, q2);
    } else {
        pushdown(left);
        if(q.s + tr[left].mn >= 0) {
            if(tr[u].l != tr[u].r) {
                Q q2 = {tr[left].s, tr[left].mn, tr[left].mx, tr[left].mnIdx, tr[left].mxIdx};
                merge(q, q2);
            }
             
            if(tr[u].l != tr[u].r) {
                dfs(q, right);
            }
        } else {
            if(tr[u].l != tr[u].r) {
                dfs(q, left);
            }
        }
    }
}

Q query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    pushdown(u);
    if(l == s && r == e){
        Q q = {tr[u].s, tr[u].mn, tr[u].mx, tr[u].mnIdx, tr[u].mxIdx, u};
        return q;
    }
    int left = u * 2 + 1, right = u * 2 + 2;
    if(e <= mid){
        return query(left, s, e);
    } else {
        return query(right, s, e);
    }
}


void goup(Q& q) {
    int u = q.u;
    while(u != 0) {
        int pa = (u - 1) / 2;
        pushdown(pa);
        pushdown(u);
        if(pa * 2 + 1 == u) { //left child
            int right = u + 1;
            pushdown(right);
            if(q.s + tr[right].mn >= 0) {
                //can whole merge
                Q q1 = {tr[right].s, tr[right].mn, tr[right].mx, tr[right].mnIdx, tr[right].mxIdx};
                merge(q, q1);
                u = pa;
            } else { //partial merge
                dfs(q, right);
                break;
            }
        } else {
            u = pa;
        }
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    tr[0] = {1, n, 0, INF, -1, -INF, -1};
    build(s, 0);
    
    for(int i = 0; i < m; i++) {
        int op;
        cin >> op;
        if(op == 1) {
            int l, r;
            cin >> l >> r;
            update(0, l, r);
        } else {
            int L;
            cin >> L;
            stop = false;
            Q q = query(0, L, L);
            goup(q);
            if(q.mn == 0) cout << q.mnIdx << endl;
            else cout << 0 << endl;
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
