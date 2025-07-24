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
struct Node {
    int l, r;
    int s, ls, rs, ms;
} tr[N * 4];

void build(int u) {
    if(tr[u].l == tr[u].r) return;
    int l = tr[u].l, r = tr[u].r;
    int mid = l + (r - l) / 2;
    tr[u * 2 + 1] = {l, mid, 0, 0, 0, 0};
    tr[u * 2 + 2] = {mid + 1, r, 0, 0, 0, 0};
    build(u * 2 + 1);
    build(u * 2 + 2);
}

void pushup(int u) {
    if(tr[u].l == tr[u].r) return;
    int left = u * 2 + 1, right = u * 2 + 2;

    tr[u].s = tr[left].s + tr[right].s;

    tr[u].ls = max(tr[left].ls, tr[left].s + max(tr[right].ls, 0));
    tr[u].rs = max(tr[right].rs, tr[right].s + max(0, tr[left].rs));

    tr[u].ms = max(tr[left].ms, tr[right].ms);
    tr[u].ms = max(tr[u].ms, max(tr[u].ls, tr[u].rs));
    tr[u].ms = max(tr[u].ms, tr[left].rs + tr[right].ls);
}

void update(int u, int index, int val) {
    if(tr[u].l == tr[u].r) {
        tr[u].ls = tr[u].rs = tr[u].s = tr[u].ms = val;
        return;
    }
    int mid = (tr[u].l) + (tr[u].r - tr[u].l) / 2;
    if(index <= mid) {
        update(u * 2 + 1, index, val);
    } else {
        update(u * 2 + 2, index, val);
    }
    pushup(u);
}

struct Q {
    int s, ls, rs, ms;
};

Q merge(Q q1, Q q2) {
    Q ans = {};
    ans.s = q1.s + q2.s;
    ans.ls = max(q1.ls, q1.s + max(q2.ls, 0));
    ans.rs = max(q2.rs, q2.s + max(q1.rs, 0));
    ans.ms = max(q1.ms, q2.ms);
    ans.ms = max(ans.ms, max(ans.ls, ans.rs));
    ans.ms = max(ans.ms, q1.rs + q2.ls);
    return ans;
}

Q query(int u, int s, int e) {
    int l = tr[u].l, r = tr[u].r;
    if(l == s && r == e) {
        return {tr[u].s, tr[u].ls, tr[u].rs, tr[u].ls};
    }
    int mid = l + (r - l) / 2;
    if(e <= mid) {
        return query(u * 2 + 1, s, e);
    } else if(s > mid) {
        return query(u * 2 + 2, s, e);
    } else {
        return merge(query(u * 2 + 1, s, mid), query(u * 2 + 2, mid + 1, e));
    }
}


int a[N];
int L[N], R[N];
vector<int> p[N];
void solve() {
    int n;
    cin >> n;
    int mx = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
        L[i] = 0;
        R[i] = n - 1;
    }

    vector<int> stk;
    for(int i = 0; i < n; i++) {
        while(stk.size() > 0 && a[i] < a[stk.back()]) {
            int j = stk.back(); stk.pop_back();
            R[j] = i - 1;
        }
        stk.push_back(i);
    }

    stk.clear();
    for(int i = n - 1; i >= 0; i--) {
        while(stk.size() > 0 && a[i] <= a[stk.back()]) {
            int j = stk.back(); stk.pop_back();
            L[j] = i + 1; 
        }
        stk.push_back(i);
    }

    for(int i = 0; i <= mx; i++) {
        p[i].clear();
    }
    for(int i = 0; i < n; i++) {
        p[a[i]].push_back(i);
    }

    tr[0] = {0, n - 1, 0, 0, 0, 0};
    build(0);
    for(int i = 0; i < n; i++) {
        update(0, i, 1);
    }

    int ans = 0;
    for(int r = 1, l = 1; r <= mx; r++) {
        while(l < r) {
            if(p[l].size() == 0) {
                l++;
                continue;
            }
            bool found = false;
            while(p[l].size() > 0 && !found) {
                int j = p[l].back();
                Q q1 = query(0, j, R[j]);
                Q q2 = query(0, L[j], j);
                if(q1.ls >= 0 || q2.rs >= 0) {
                    found = true;
                    ans = max(ans, r - l);
                } else {
                    p[l].pop_back();
                }
            }
            if(found) break;
            l++;
        }

        for(int pos : p[r]) {
            update(0, pos, -1);
        }
        
    }
    cout << ans << endl;
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
