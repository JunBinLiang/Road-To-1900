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

const int MAX = 2e5 + 10;
const int INF = 1e9 + 10;
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
} seg;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];

    seg.tr[0] = {0, n, -INF};
    seg.build(0);
    for(int i = 0; i < n; i++) {
        seg.update(0, i, a[i]);
    }
    
    long long ans = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] == b[i]) {
            int lsz = i;
            int rsz = n - (i + 1);
            ans += (lsz + 1ll) * (rsz + 1ll);
            continue;
        }

        int t = -1;
        if(a[i] > b[i]) {
            t = a[i];
        } else {
            t = b[i];
        }

        int l = 0, r = i - 1;
        int p = -1;
        while(l <= r) {
            int mid = l + (r - l) / 2;
            int mx = seg.query(0, mid, i - 1);
            if(mx >= t) {
                p = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        if(p != -1) {
            ans += (n - i + 0ll) * (p + 1);
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
