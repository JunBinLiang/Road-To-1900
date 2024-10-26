#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string.h>


using namespace std;  
const int N = 2e5 + 10;
int last[N], extend[N];

const int INF = 1e8;
const int MAX = 200000 + 100;
struct MinSeg {
    struct Node {
        int l, r;
        int mn;
    } tr[MAX * 4];

    void build(int id) {
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            return;
        }
        int mid = l + (r - l) / 2;
        tr[id * 2 + 1] = {l, mid, INF};
        tr[id * 2 + 2] = {mid + 1, r, INF};
        build(id * 2 + 1);
        build(id * 2 + 2);
    }

    void update(int id, int index, int val) { 
        int l = tr[id].l, r = tr[id].r;
        if(l == r) {
            tr[id].mn = min(tr[id].mn, val);  
            return;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(index <= mid) {
            update(left, index, val);
        } else {
            update(right, index, val);
        }
        tr[id].mn = min(tr[left].mn, tr[right].mn);
    }

    int query(int id, int s, int e) {
        int l = tr[id].l, r = tr[id].r;
        if(l == s && r == e){
            return tr[id].mn;
        }
        int mid = l + (r - l) / 2;
        int left = id * 2 + 1, right = id * 2 + 2;
        if(e <= mid){
            return query(left, s, e);
        } else if(s >= mid + 1) {
            return query(right, s, e);
        } else {
            return min(query(left, s, mid), query(right, mid + 1, e));
        }
    }
} minseg;

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
} maxseg;

void solve() {
    int n, m;
    cin >> n >> m;
    
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    for(int i = 0; i <= n; i++) last[i] = 0;
    maxseg.tr[0] = {0, n, -INF};
    maxseg.build(0);
    vector<int> dp(n + 1);
    for(int i = 1; i <= n; i++) {
        if(last[a[i]] == 0) { //first appear
            extend[a[i]] = 0;
        } else {
            int l = 1;
            int r = last[a[i]] - 1;
            int pos = last[a[i]];
            while(l <= r) {
                int mid = l + (r - l) / 2;
                if(maxseg.query(0, mid, last[a[i]] - 1) > last[a[i]]) {
                    l = mid + 1;
                } else {
                    pos = mid;
                    r = mid - 1;
                }
            }
            extend[a[i]] = max(extend[a[i]], pos);
            maxseg.update(0, last[a[i]], i);
        }
        dp[i] = extend[a[i]];
        last[a[i]] = i;
    }

    maxseg.tr[0] = {0, n, -INF};
    maxseg.build(0);
    for(int i = 1; i <= n; i++) {
        maxseg.update(0, i, dp[i]);
    }
    
    for(int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        if(maxseg.query(0, l, r) > l) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
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
