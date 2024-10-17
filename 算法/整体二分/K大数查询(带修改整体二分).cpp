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

const int N = 2e5 + 10, INF = 1e8;
int n, m;
int a[N], ans[N];

struct Query {
    int op, l, r, i;
    long long k;
} q[N], q1[N], q2[N];


namespace SegmentTreeRangeAdd {
    struct Node { //Segment Tree for range update
        int l, r, add; long long s;
    } tr[N * 4];
    void build(int u) {
        if(tr[u].l == tr[u].r) return;
        int left = u * 2 + 1, right = u * 2 + 2;
        int l = tr[u].l, r = tr[u].r;
        int mid = l + (r - l) / 2;
        tr[left] = {l, mid, 0, 0};
        tr[right] = {mid + 1, r, 0, 0};
        build(left); build(right);
    }   

    void pushdown(int u) {
        if(tr[u].l == tr[u].r || tr[u].add == 0) return;
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[left].s += ((tr[left].r - tr[left].l + 1ll) * tr[u].add);
        tr[right].s += ((tr[right].r - tr[right].l + 1ll) * tr[u].add);
        tr[right].add += tr[u].add;
        tr[left].add += tr[u].add;
        tr[u].add = 0;
    }

    void pushup(int u) {
        int left = u * 2 + 1, right = u * 2 + 2;
        tr[u].s = tr[left].s + tr[right].s;
    }

    void update(int u, int s, int e, int val) { 
        int l = tr[u].l, r = tr[u].r;
        if(l == s && r == e) {
            tr[u].add += val;
            tr[u].s += ((tr[u].r - tr[u].l + 1ll) * val); 
            return;
        }

        int mid = l + (r - l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        pushdown(u);

        if(e <= mid) {
            update(left, s, e, val);
        } else if(s >= mid + 1) {
            update(right, s, e, val);
        } else {
            update(left, s, mid, val);
            update(right, mid + 1, e, val);
        }
        pushup(u);
    }

    long long query(int u, int s, int e) { // query sum from [0 : l]
        int l = tr[u].l, r = tr[u].r;
        if(l == s && r == e){
            return tr[u].s;
        }
        pushdown(u);
        int mid = l + (r - l) / 2;
        int left = u * 2 + 1, right = u * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return query(left, s, mid) + query(right, mid + 1, e);
        }
    }
}


//找第k大
void dfs(int l, int r, int L, int R) {
    if(l == r) {
        for(int i = L; i <= R; i++) {
            if(q[i].op == 2) {
                ans[q[i].i] = l;
            }
                
        }
        return;
    }
    
    long long mid = l + (r - l) / 2;
    
    //cout << "gg " << l << " " << r << " " << mid << endl;
    
    int t1 = 0, t2 = 0;
    for(int i = L; i <= R; i++) {
        if(q[i].op == 1) { //update
            if(q[i].k > mid) {
                SegmentTreeRangeAdd :: update(0, q[i].l, q[i].r, 1);
                //cout << "update  " << l << " "  << r << "   |" << q[i].l << " " << q[i].r + 1 << endl;
                q2[t2++] = q[i];
            } else {
                q1[t1++] = q[i];
            }
        } else {
            long long cnt = SegmentTreeRangeAdd :: query(0, q[i].l, q[i].r);
            //cout << l << "  " << r << "  " << mid << "    |" << cnt << endl;
            if(q[i].k <= cnt) {
                q2[t2++] = q[i];
            } else {
                q[i].k -= cnt;
                q1[t1++] = q[i];
            }
        }
    }

    for(int i = 0; i < t2; i++) {
        if(q2[i].op == 1) {
            //cout << "delete  " << l << " "  << r << "  |" << q[i].l << " " << q[i].r + 1 << endl;
            SegmentTreeRangeAdd :: update(0, q2[i].l, q2[i].r, -1);
        }
    }

    for(int i = 0; i < t1; i++) {
        q[i] = q1[i];
    }
    for(int i = 0; i < t2; i++) {
        q[i + t1] = q2[i];
    }
    if(t1 > 0)
        dfs(l, mid, 0, t1 - 1);
    if(t2 > 0)
        dfs(mid + 1, r, t1, t1 + t2 - 1);
}

void solve() {
    cin >> n >> m;
    
    for(int i = 0; i < N; i++) {
        ans[i] = INF;
    }

    for(int i = 0; i < m; i++) {
        cin >> q[i].op >> q[i].l >> q[i].r >> q[i].k;
        q[i].i = i;
    }

    SegmentTreeRangeAdd :: tr[0] = {0, n + 2, 0, 0};
    SegmentTreeRangeAdd :: build(0);
    dfs(-200000, 200000, 0, m - 1);
    
    for(int i = 0; i < m; i++) {
        if(ans[i] != INF) {
            cout << ans[i] << endl;
        }
    }
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
